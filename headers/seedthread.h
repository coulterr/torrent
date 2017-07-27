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
int Seedthread_kill(Seedthread *seedthread); 
void *Seedthread_start(void *args); 
int Seedthread_delete(void *seedthread); 

#endif
