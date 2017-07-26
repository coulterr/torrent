#ifndef SEEDTHREAD_H
#define SEEDTHREAD_H

#include <semaphore.h>
#include "arraylist.h"

struct seedthread_args {
	Arraylist *torrents; 
	sem_t *parent_killswitch; 
};

void start_seedthread(void *args);


#endif
