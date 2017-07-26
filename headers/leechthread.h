#ifndef LEECHTHREAD_H
#define LEECHTHREAD_H

#include <semaphore.h>
#include <pthread.h>
#include "segmentinfo.h"
#include "torrentinfo.h"
#include "shqueue.h"

typedef struct {
	Shqueue *leechqueue; 	
	sem_t parent_killswitch; 
	pthread_t thread;
}Leechthread;

struct leechpair {
	Segmentinfo *segment; 
	Torrentinfo *torrent; 
};

int Leechthread_init(Leechthread **leechthread); 
int Leechthread_enqueue(Leechthread *leechthread, Segmentinfo *segment, Torrentinfo *torrent);
int Leechthread_kill(Leechthread *leechthread);
int Leechthread_delete(Leechthread *leechthread);
void *Leechthread_start(void *args);

#endif