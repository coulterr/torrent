#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include <iostream>
#include <openssl/sha.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "bin_to_hex.h"

void print_hash(unsigned char *hash) 
{
	for(int i = 0; i < SHA_DIGEST_LENGTH * 2; i++)
	{
		printf("%c", hash[i]); 
	}
	printf("\n"); 
}


int main (int argc, char **argv)
{
	const int BLOCK_SIZE = 16000; 
	char *file_path = argv[1]; 
	char *hashes_path = argv[2]; 

	FILE *file = fopen(file_path, "r"); 
	FILE *hashes = fopen(hashes_path, "r"); 

	unsigned char buff[BLOCK_SIZE]; 
	unsigned char hash[SHA_DIGEST_LENGTH]; 
	unsigned char hex[SHA_DIGEST_LENGTH * 2]; 
	unsigned char check_hex[SHA_DIGEST_LENGTH * 2]; 

	int len; 
	int i = 0; 
	while(len = fread(buff, sizeof(char), BLOCK_SIZE, file))
	{
		SHA1(buff, len, hash); 
		bin_to_hex(hex, hash, SHA_DIGEST_LENGTH);
		fread(check_hex, sizeof(char), SHA_DIGEST_LENGTH * 2, hashes); 
		if (memcmp(hex, check_hex, SHA_DIGEST_LENGTH * 2) == 0) {
			printf("Block %i: SUCCESS\n", i); 
		}else {
			printf("Block %i: FAIL\n", i); 
			print_hash(hex); 
			print_hash(check_hex); 
		}

		i++; 
		
	}

	fclose(file); 
	fclose(hashes); 
}
