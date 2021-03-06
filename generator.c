#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>

#include "headers/hash_functions.h"
#include "headers/charlist.h"

char *generate_file_metadata(const char *src_path, FILE *metafile)
{	
	FILE *source = fopen(src_path, "r"); 
	unsigned char buff[META_BLOCK_LENGTH]; 
	unsigned char hex[SHA1_HEX_LENGTH]; 

	fwrite(src_path, sizeof(char), strlen(src_path), metafile); 
	fwrite("\n", sizeof(char), 1, metafile); 

	Charlist *charlist; 
	Charlist_init(&charlist); 

	size_t sum = 0; 
	size_t len;

	while(len = fread(buff, sizeof(char), META_BLOCK_LENGTH, source)) 
	{
		sum += len; 
		to_sha1_hex(hex, buff, len); 
		Charlist_add(charlist, hex, SHA1_HEX_LENGTH); 
	}
	
	fprintf(metafile, "%i\n", sum); 
	
	for (size_t i = 0; i < (sum + (META_BLOCK_LENGTH - 1)) / META_BLOCK_LENGTH; i++)
	{
		fwrite((charlist -> data) + SHA1_HEX_LENGTH * i, sizeof(char), SHA1_HEX_LENGTH, metafile); 
	}
	fwrite("\n", sizeof(char), 1, metafile); 

	Charlist_delete(charlist); 

	fclose(source); 
}


void generate_metadata(const char *src_dir, FILE *metafile)
{
	DIR *dir; 
	struct dirent *entry; 
	if (!(dir = opendir(src_dir))) return; 
	while ((entry = readdir(dir)) != NULL) {
		char path[1024]; 
		snprintf(path, sizeof(path), "%s/%s", src_dir, entry->d_name); 
		if (entry->d_type == DT_REG) {
			generate_file_metadata((const char *) path, metafile); 
		}
		else if (entry->d_type == DT_DIR) {
			if (strcmp(entry->d_name , ".") == 0 || strcmp(entry->d_name, "..") == 0) {
				continue; 
			}
			else {
				generate_metadata((const char *) path, metafile); 
			}
		}
	}
	closedir(dir); 
}


int main (int argc, char **argv)
{
	const char *src_dir = argv[1]; 
	const char *meta_path = argv[2]; 

	FILE *metafile = fopen(meta_path, "w"); 
	fwrite("0000000000", sizeof(char), 10, metafile); 
	fwrite("\n", sizeof(char), 1, metafile); 
	
	generate_metadata(src_dir, metafile);

	fclose(metafile); 

}
