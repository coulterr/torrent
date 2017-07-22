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
#include "headers/charlist.h"

char *generate_file_metadata(const char *src_path, const char *meta_path, const size_t block_size)
{	
	size_t hex_length = SHA_DIGEST_LENGTH * 2; 
	FILE *source = fopen(src_path, "r"); 
	FILE *dest = fopen(meta_path, "a"); 
	unsigned char buff[block_size]; 
	unsigned char hash[SHA_DIGEST_LENGTH]; 
	unsigned char hex[hex_length]; 

	fwrite(src_path, sizeof(char), strlen(src_path), dest); 
	fwrite("\n", sizeof(char), 1, dest); 

	Charlist *charlist; 
	Charlist_init(&charlist); 

	size_t sum = 0; 
	size_t len;

	while(len = fread(buff, sizeof(char), block_size, source)) 
	{
		sum += len; 
		SHA1(buff, len, hash); 
		bin_to_hex(hex, hash, SHA_DIGEST_LENGTH);
		Charlist_add(charlist, hex, hex_length); 
	}
	
	fprintf(dest, "%i\n", sum); 
	
	for (size_t i = 0; i < (sum + (block_size - 1)) / block_size; i++)
	{
		fwrite((charlist -> data) + hex_length * i, sizeof(char), hex_length, dest); 
	}
	fwrite("\n", sizeof(char), 1, dest); 

	Charlist_delete(charlist); 
	free(charlist); 

	fclose(source); 
	fclose(dest); 
}


void generate_metadata(const char *src_dir, const char *meta_path, const size_t block_size)
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
	const size_t block_size = 16000; 
	const char *src_dir = argv[1]; 
	const char *meta_path = argv[2]; 

	generate_metadata(src_dir, meta_path, block_size); 	
}
