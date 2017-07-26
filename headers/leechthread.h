#ifndef LEECHTHREAD_H
#define LEECHTHREAD_H

#include <semaphore.h>
#include "shqueue.h"

struct leechthread_args {
	Shqueue *leechqueue; 	
	sem_t *parent_killswitch; 
};

void start_leechthread(void *args);


#endif
