#include "headers/metainfo_parser.h"

void print_info(Torrentinfo *info)
{
	Arraylist *files = info->files; 
	Arraylist *segments = info->segments; 

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

		for(size_t j = 0; j < (sinfo->byte_count + (META_BLOCK_LENGTH - 1)) / META_BLOCK_LENGTH; j++)
		{
			for(size_t k = 0; k < SHA1_HEX_LENGTH; k++)
			{
				printf("%c", (sinfo->hashes)[SHA1_HEX_LENGTH * j + k]); 
			}
			printf("\n"); 
		}

		printf("\n"); 
	}
}

int read_line(unsigned char *buff, FILE *file)
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

int dump_to_map(char *map_path, Arraylist *torrents)
{
	FILE *mapfile = fopen(map_path, "w"); 

	for(size_t i = 0; i < torrents->size; i++)
	{
		Torrentinfo *info = (Torrentinfo *) Arraylist_get(torrents, i); 
		fwrite(info->metapath, sizeof(char), strlen(info->metapath), mapfile); 
		fwrite("\n", sizeof(char), 1, mapfile); 
		fwrite(info->dirpath, sizeof(char), strlen(info->dirpath), mapfile); 
		fwrite("\n", sizeof(char), 1, mapfile); 

		Arraylist *segments = info->segments; 
		
		unsigned char statuses[segments->size];
		for(size_t j = 0; j < segments->size; j++)
		{
			Segmentinfo *segment = Arraylist_get(segments, j); 
			statuses[j] = (segment->status) + 48; 		
		}

		fwrite(statuses, sizeof(char), segments->size, mapfile); 
		fwrite("\n", sizeof(char), 1, mapfile); 
	}
}


int get_torrent_meta_info(Torrentinfo *info) 
{
	unsigned char *meta_path = info->metapath; 
	Arraylist *files = info->files; 
	Arraylist *segments = info->segments; 
	

	FILE *metafile;
	if(!(metafile = fopen(meta_path, "r"))) return -1; 
	 
	unsigned char buff[1024]; 

	read_line(buff, metafile); 
	strcpy(info->id, buff); 

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

	return 0; 
}

int get_meta_info(Arraylist *torrents, char *map_path)
{
	FILE *mapfile; 
	if(!(mapfile = fopen(map_path, "r"))){
		return -1; 
	}
	
	unsigned char buffer[250000]; 

	while(read_line(buffer, mapfile) > 0)
	{
		Torrentinfo *info; 
		Torrentinfo_init(&info); 
		strcpy(info->metapath, buffer); 
		read_line(buffer, mapfile); 
		strcpy(info->dirpath, buffer); 

		if(get_torrent_meta_info(info) == -1) return -1; 
		
		Arraylist *segments = info->segments; 
		read_line(buffer, mapfile); 
		
		for(size_t i = 0; i < segments->size; i++)
		{
			Segmentinfo *segment = Arraylist_get(segments, i); 
			segment->status = buffer[i] - 48; 
		}
			
		Arraylist_add(torrents, info); 
	}

	fclose(mapfile); 
	return 0; 		
}

