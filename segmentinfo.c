#include "headers/segmentinfo.h"


int Segmentinfo_init(Segmentinfo **sinfo)
{
	*sinfo = malloc(sizeof(Segmentinfo)); 
	(*sinfo)->status = 0; 
}


int Segmentinfo_clean(void *sinfo)
{
	free(sinfo); 
}
