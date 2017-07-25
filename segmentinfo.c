#include "headers/segmentinfo.h"


int Segmentinfo_init(Segmentinfo **sinfo)
{
	if(!(*sinfo = malloc(sizeof(Segmentinfo)))){
		perror("Failed to allocate Segmentinfo\n"); 
		exit(0); 
	}
	(*sinfo)->status = 0; 
}


int Segmentinfo_delete(void *sinfo)
{
	free(sinfo); 
}
