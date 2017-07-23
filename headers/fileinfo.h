#ifndef FILEINFO_H
#define FILEINFO_H

#include <stdlib.h>
#include <semaphore.h>

typedef struct {
	char path[1024]; 
	sem_t *lock; 
}Fileinfo; 

int Fileinfo_init(Fileinfo **finfo);
int Fileinfo_delete(void *finfo);

#endif
