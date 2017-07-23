#include "headers/metainfo_parser.h"
#include "headers/torrentinfo.h"

int print_info(Arraylist *files, Arraylist *segments)
{
	size_t block_size = 16000; 
	size_t segment_size = 256; 
	size_t hex_len = 40; 


	for(size_t i = 0; i < files->size; i++)
	{
		Fileinfo *finfo = (Fileinfo *) Arraylist_get(files, i);
		printf("Path %ld: %s\n", i, finfo->path); 
	}


	for(size_t i = 0; i < segments->size; i++)
	{
		Segmentinfo *sinfo = (Segmentinfo *) Arraylist_get(segments, i); 	
		printf("SEGMENT %ld\n", i); 
		printf("File index: %ld\n", sinfo->file_index); 
		printf("Offset: %ld\n", sinfo->offset); 
		printf("Byte Count: %ld\n", sinfo->byte_count); 

		for(size_t j = 0; j < (sinfo->byte_count + (block_size - 1)) / block_size; j++)
		{
			for(size_t k = 0; k < hex_len; k++)
			{
				printf("%c", (sinfo->hashes)[hex_len * j + k]); 
			}
			printf("\n"); 
		}

		printf("\n"); 
	}
}



int main(int argc, char **argv)
{
	Torrentinfo *info; 
	Torrentinfo_init(&info, argv[1], ""); 

	get_meta_info(info); 

//	print_info(info->files, info->segments); 

	Torrentinfo_delete(info); 
}

