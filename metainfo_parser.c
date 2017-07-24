#include "headers/metainfo_parser.h"

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

int get_meta_info(Torrentinfo *info) 
{
	char *meta_path = info->metapath; 
	Arraylist *files = info->files; 
	Arraylist *segments = info->segments; 
	

	FILE *metafile = fopen(meta_path, "r"); 
	char buff[1024]; 

	while(read_line(buff, metafile) > 0)
	{
		Fileinfo *finfo; 
		Fileinfo_init(&finfo); 
		strcpy(finfo->path, buff); 
		size_t file_index = Arraylist_add(files, (void *) finfo); 

		read_line(buff, metafile);
		long long byte_count = atoll(buff);
		
		long long block_count = (byte_count + (META_BLOCK_LENGTH - 1)) / META_BLOCK_LENGTH; 
		long long segment_count = (block_count + (META_SEGMENT_LENGTH - 1)) / META_SEGMENT_LENGTH; 
		
		for(long long i = 0; i < segment_count; i++)
		{
			Segmentinfo *sinfo; 
			Segmentinfo_init(&sinfo); 
			
			sinfo->file_index = file_index; 
			sinfo->offset = i * (META_SEGMENT_LENGTH * META_BLOCK_LENGTH); 
			

			if(i == segment_count - 1){
				sinfo->byte_count = byte_count - (i * (META_BLOCK_LENGTH * META_SEGMENT_LENGTH)); 
			}else {
				sinfo->byte_count = META_BLOCK_LENGTH * META_SEGMENT_LENGTH; 
			}
			
			for(long long j = 0; j < (sinfo -> byte_count + (META_BLOCK_LENGTH - 1)) / META_BLOCK_LENGTH; j++) 
			{
				fread(sinfo->hashes + (j * SHA1_HEX_LENGTH), sizeof(char), SHA1_HEX_LENGTH, metafile); 		
			}

			Arraylist_add((void *)segments, sinfo); 
		}
		fread(buff, sizeof(char), 1, metafile); //read newline character
	}
}
