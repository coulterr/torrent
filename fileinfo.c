#include "headers/fileinfo.h"

int Fileinfo_init(Fileinfo **finfo)
{
	*finfo = malloc(sizeof(Fileinfo)); 
	sem_init(&((*finfo)->lock), 0, 1); 
}

int Fileinfo_clean(void *finfo)
{
	sem_destroy(&(((Fileinfo *)(finfo))->lock)); 
	free(finfo); 
}
