#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <openssl/sha.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>

#include "headers/bin_to_hex.h"


char *generate_file_metadata(const char *src_path, const char *meta_path, const int block_size)
{		
	FILE *source = fopen(src_path, "r"); 
	FILE *dest = fopen(meta_path, "a"); 
	unsigned char buff[block_size]; 
	unsigned char hash[SHA_DIGEST_LENGTH]; 
	unsigned char hex[SHA_DIGEST_LENGTH * 2]; 

	fwrite(src_path, sizeof(char), strlen(src_path), dest); 
	fwrite("\n", sizeof(char), 1, dest); 

	int sum = 0; 
	size_t len;

	while(len = fread(buff, sizeof(char), block_size, source)) 
	{
		SHA1(buff, len, hash); 
		bin_to_hex(hex, hash, SHA_DIGEST_LENGTH);
		fwrite(hex, sizeof(char), SHA_DIGEST_LENGTH * 2, dest); 
	}

	fwrite("\n", sizeof(char), 1, dest); 
	
	fclose(source); 
	fclose(dest); 
}


void generate_metadata(const char *src_dir, const char *meta_path, const int block_size)
{
	DIR *dir; 
	struct dirent *entry; 
	if (!(dir = opendir(src_dir))) return; 
	while ((entry = readdir(dir)) != NULL) {
		char path[1024]; 
		snprintf(path, sizeof(path), "%s/%s", src_dir, entry->d_name); 
		if (entry->d_type == DT_REG) generate_file_metadata((const char *) path, meta_path, block_size); 
		else if (entry->d_type == DT_DIR) {
			if (strcmp(entry->d_name , ".") == 0 || strcmp(entry->d_name, "..") == 0) continue; 
			generate_metadata((const char *) path, meta_path, block_size); 
		}
	}
	closedir(dir); 
}


int main (int argc, char **argv)
{
	const int block_size = 16000; 
	const char *src_dir = argv[1]; 
	const char *meta_path = argv[2]; 

	generate_metadata(src_dir, meta_path, block_size); 	
}
