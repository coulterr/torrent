#include "headers/fileinfo.h"

int Fileinfo_init(Fileinfo **finfo)
{
	*finfo = malloc(sizeof(Fileinfo)); 
	(*finfo)->lock = malloc(sizeof(sem_t)); 
	sem_init((*finfo)->lock, 0, 1); 
}

int Fileinfo_delete(void *finfo)
{
	sem_destroy(((Fileinfo *)finfo)->lock); 
	free(((Fileinfo *) finfo)->lock); 
	free(finfo); 
}
