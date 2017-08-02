#ifndef LEECH_CONNECTION_THREAD_H
#define LEECH_CONNECTION_THREAD_H

#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include "arraylist.h"
#include "torrentinfo.h"
#include "segmentinfo.h"
#include "fileinfo.h"
#include "shqueue.h"

typedef struct {
	Torrentinfo *torrent; 
	//connection address 
	pthread_t thread;
}Leech_connection_thread;


int Leech_connection_thread_init(Leech_connection_thread **leech_connection_thread, Torrentinfo *torrent); 
int Leech_connection_thread_delete(void *leech_connection_thread);
void *Leech_connection_thread_start(void *args);

#endif
