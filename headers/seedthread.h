#ifndef SEEDTHREAD_H
#define SEEDTHREAD_H

#include <semaphore.h>
#include <pthread.h>
#include "arraylist.h"

typedef struct {
	Arraylist *torrents; 
	sem_t parent_killswitch; 
	pthread_t thread; 
}Seedthread;

int Seedthread_init(Seedthread **seedthread, Arraylist *torrents); 
void *Seedthread_start(void *args); 

#endif
