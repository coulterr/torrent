#ifndef LEECH_CONTROL_THREAD_H
#define LEECH_CONTROL_THREAD_H

#include <semaphore.h>
#include <pthread.h>
#include "arraylist.h"
#include "torrentinfo.h"
#include "segmentinfo.h"
#include "fileinfo.h"
#include "shqueue.h"
#include "leech_connection_thread.h"

typedef struct {
	Torrentinfo *torrent; 
	sem_t killswitch; 
	pthread_t thread;
}Leech_control_thread;


int Leech_control_thread_init(Leech_control_thread **leech_control_thread, Torrentinfo *torrent); 
int Leech_control_thread_kill(Leech_control_thread *leech_control_thread);
int Leech_control_thread_delete(void *leech_control_thread);
void *Leech_control_thread_start(void *args);

#endif
