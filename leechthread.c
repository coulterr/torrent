#include "headers/leechthread.h"


int Leechthread_init(Leechthread **leechthread)
{
	*leechthread = malloc(sizeof(leechthread)); 
	(*leechthread)->leechqueue = malloc(sizeof(Shqueue)); 
	Shqueue_init(&((*leechthread)->leechqueue)); 

	sem_init(&((*leechthread)->parent_killswitch), 0, 0);
	
	pthread_create(&((*leechthread)->thread), NULL, &Leechthread_start, (void *) *leechthread); 
}

int Leechthread_enqueue(Leechthread *leechthread, Segmentinfo *segment, Torrentinfo *torrent)
{
	struct leechpair *pair = malloc(sizeof(struct leechpair)); 
	pair->segment = segment; 
	pair->torrent = torrent; 
	
	Shqueue_push(leechthread->leechqueue, (void *) pair); 	
}


int Leechthread_kill(Leechthread *leechthread)
{
	sem_post(&(leechthread->parent_killswitch)); 
}

int Leechthread_delete(Leechthread *leechthread)
{
	Shqueue_delete(leechthread->leechqueue, NULL); 
	sem_destroy(&(leechthread->parent_killswitch)); 

	free(leechthread); 
}

void *Leechthread_start(void *args)
{

}
