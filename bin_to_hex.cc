#include "bin_to_hex.h"

void bin_to_hex(unsigned char *str) 
{
	unsigned char map[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'}; 
	int len = 20; 
	unsigned char expanded_str[len * 2]; 
	
	int i = 0;
	for(int j = 0; j < len * 2; j+=2)
	{
		expanded_str[j] = str[i] >> 4; 
		expanded_str[j+1] = str[i] << 4; 
		expanded_str[j+1] = expanded_str[j+1] >> 4; 
		i++; 
	}

	unsigned char output[(len * 2) + 1] ; 
	for(i = 0; i < (len*2); i++)
	{
		output[i] = map[expanded_str[i]]; 	
	}
	output[len * 2] = 0; 

	for(i = 0; i < len * 2; i++)
	{
		printf("%c", output[i]); 
	}

	printf("\n"); 
}
