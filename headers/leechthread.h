#ifndef LEECHTHREAD_H
#define LEECHTHREAD_H

#include <semaphore.h>
#include <pthread.h>
#include "arraylist.h"
#include "torrentinfo.h"
#include "segmentinfo.h"
#include "fileinfo.h"
#include "shqueue.h"
#include "leech_control_thread.h"

typedef struct {
	Arraylist *torrents; 
	sem_t parent_killswitch; 
	pthread_t thread;
}Leechthread;


int Leechthread_init(Leechthread **leechthread, Arraylist *torrents); 
int Leechthread_kill(Leechthread *leechthread);
int Leechthread_delete(Leechthread *leechthread);
void *Leechthread_start(void *args);

#endif
