#include "headers/validator.h"


int read_line(char *buff, FILE *file)
{
	size_t i = 0; 
	char c; 
	
	while(fread(&c, sizeof(char), 1, file))
	{
		if(c == '\n') break; 
		buff[i] = c;
		i++; 
	}
	
	buff[i] = '\0';
	return i; 
}

int get_meta_info(const char *meta_path, Arraylist *files, Arraylist *segments) 
{
	FILE *metafile = fopen(meta_path, "r"); 
	size_t hex_len = SHA_DIGEST_LENGTH * 2; 	
	int block_len = 16000;
	int segment_len = 256;  
	char buff[1024]; 

	while(read_line(buff, metafile) > 0)
	{
		Fileinfo *finfo; 
		Fileinfo_init(&finfo); 
		strcpy(finfo->path, buff); 
		size_t file_index = Arraylist_add(files, (void *) finfo); 

		read_line(buff, metafile);
		long long byte_count = atoll(buff);
		
		long long block_count = (byte_count + (block_len - 1)) / block_len; 
		long long segment_count = (block_count + (segment_len - 1)) / segment_len; 
		
		for(long long i = 0; i < segment_count; i++)
		{
			Segmentinfo *sinfo; 
			Segmentinfo_init(&sinfo); 
			
			sinfo->file_index = file_index; 
			sinfo->offset = i * (segment_len * block_len); 
			

			if(i == segment_count - 1){
				sinfo->byte_count = byte_count - (i * (block_len * segment_len)); 
			}else {
				sinfo->byte_count = block_len * segment_len; 
			}
			
			for(long long j = 0; j < (sinfo -> byte_count + (block_len - 1)) / block_len; j++) 
			{
				fread(sinfo->hashes + (j * hex_len), sizeof(char), hex_len, metafile); 		
			}

			Arraylist_add((void *)segments, sinfo); 
		}
		fread(buff, sizeof(char), 1, metafile); //read newline character

		printf("File: %s\nCount: %ld\n", finfo->path, byte_count); 
	}
}


int main (int argc, char **argv)
{
	Arraylist *files; 
	Arraylist *segments; 

	Arraylist_init(&files); 
	Arraylist_init(&segments); 

	get_meta_info(argv[1], files, segments); 

	Arraylist_clean(files, &Fileinfo_clean); 
	Arraylist_clean(segments, &Segmentinfo_clean); 


}
