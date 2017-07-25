#include "headers/fileinfo.h"

int Fileinfo_init(Fileinfo **finfo)
{
	if(!(*finfo = malloc(sizeof(Fileinfo)))){
		perror("Failed to allocate for Fileinfo\n"); 
		exit(0); 
	}
	if(!((*finfo)->lock = malloc(sizeof(sem_t)))){
		perror("Failed to allocate for Fileinfo lock\n"); 
		exit(0); 
	}
	sem_init((*finfo)->lock, 0, 1); 
}

int Fileinfo_delete(void *finfo)
{
	if(sem_destroy(((Fileinfo *)finfo)->lock) == -1){
		perror("Failed to destroy Fileinfo lock\n"); 
		exit(0); 
	}
	free(((Fileinfo *) finfo)->lock); 
	free(finfo); 
}
