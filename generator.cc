#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include <iostream>
#include <openssl/sha.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "bin_to_hex.h"

int main (int argc, char **argv)
{
	const int BLOCK_SIZE = 16000; 

	const char *source_path = argv[1]; 
	const char *dest_path = argv[2]; 

	FILE *source = fopen(source_path, "r"); 
	FILE *dest = fopen(dest_path, "w"); 

	unsigned char buff[BLOCK_SIZE]; 
	unsigned char hash[SHA_DIGEST_LENGTH]; 
	unsigned char hex[SHA_DIGEST_LENGTH * 2]; 

	int sum = 0; 
	size_t len;

	while(len = fread(buff, sizeof(char), BLOCK_SIZE, source)) 
	{
		SHA1(buff, len, hash); 
		bin_to_hex(hex, hash, SHA_DIGEST_LENGTH);
		fwrite(hex, sizeof(char), SHA_DIGEST_LENGTH * 2, dest); 
	}

	fclose(source); 
	fclose(dest); 

	 
	
}
