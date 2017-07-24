#include "headers/hash_functions.h"

void bin_to_hex(unsigned char *dest, unsigned char *source, size_t len) 
{
	unsigned char map[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'}; 
	
	int i = 0;
	for(int j = 0; j < len * 2; j+=2)
	{
		dest[j] = source[i] >> 4; 
		dest[j+1] = source[i] << 4; 
		dest[j+1] = dest[j+1] >> 4; 
		i++; 
	}

	for(i = 0; i < (len*2); i++)
	{
		dest[i] = map[dest[i]]; 	
	}

}

void to_sha1_hex(unsigned char *hex, unsigned char *source, size_t len)
{
	unsigned char hash[SHA_DIGEST_LENGTH]; 
	SHA1(source, len, hash); 
	bin_to_hex(hex, hash, SHA_DIGEST_LENGTH);
}
