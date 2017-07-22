#include "headers/validator.h"


struct file_info 
{
	char *path; 
	long long byte_length; 
};


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

int get_meta_info(const char *meta_path)
{
	FILE *metafile = fopen(meta_path, "r"); 
	size_t hex_len = SHA_DIGEST_LENGTH * 2; 	
	size_t block_len = 16000; 
	char buff[1024]; 
	char hex[hex_len + 1];

	while(read_line(buff, metafile) > 0)
	{
		struct file_info *finfo = malloc(sizeof(struct file_info)); 
		finfo->path = malloc(strlen(buff) + 1); 
		strcpy(finfo->path, buff); 

		read_line(buff, metafile); 
		finfo->byte_length = atoll(buff); 
	
		for(long long i = 0; i < ((finfo->byte_length) + (block_len - 1)) / block_len; i++)
		{
			fread(hex, sizeof(char), hex_len + 1, metafile); 		
		}

		printf("File: %s\nCount: %ld\n", finfo->path, finfo->byte_length); 
	}
}


int main (int argc, char **argv)
{
	get_meta_info(argv[1]); 
}
