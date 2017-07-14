#include <string>
#include <iostream>
#include <openssl/sha.h>
#include "bin_to_hex.h"


int main (int argc, char ** argv) 
{
	unsigned char *str = (unsigned char *) argv[1]; 
	unsigned char hash[SHA_DIGEST_LENGTH]; 
	SHA1(str, strlen((char *) str), hash); 
	bin_to_hex(hash); 
}


