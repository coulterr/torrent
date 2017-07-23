#include "headers/segmentinfo.h"


int Segmentinfo_init(Segmentinfo **sinfo)
{
	*sinfo = malloc(sizeof(Segmentinfo)); 
	(*sinfo)->status = 0; 
}


int Segmentinfo_delete(void *sinfo)
{
	free(sinfo); 
}
