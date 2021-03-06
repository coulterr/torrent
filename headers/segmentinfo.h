#ifndef SEGMENTINFO_H 
#define SEGMENTINFO_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
	
	unsigned char status; 
	size_t file_index; 
	size_t offset; 
	size_t byte_count; 
	char hashes[4096000]; 

}Segmentinfo;


int Segmentinfo_init(Segmentinfo **sinfo);
int Segmentinfo_delete(void *sinfo);


#endif 


