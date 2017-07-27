#include "headers/leechthread.h"


int Leechthread_init(Leechthread **leechthread, Arraylist *torrents)
{
	*leechthread = malloc(sizeof(leechthread)); 
	(*leechthread)->leechqueue = malloc(sizeof(Shqueue)); 
	Shqueue_init(&((*leechthread)->leechqueue)); 

	sem_init(&((*leechthread)->parent_killswitch), 0, 0);

	for (size_t i = 0; i < torrents->size; i++) {

		Torrentinfo *torrent = Arraylist_get(torrents, i); 
		Arraylist *segments = torrent->segments; 
		
		for (size_t j = 0; j < segments->size; j++) {

			Segmentinfo *segment = Arraylist_get(segments, j); 
			Leechthread_enqueue(*leechthread, segment, torrent); 
		}
	}


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
	Leechthread *self = (Leechthread *) args; 

	printf("Leechthread started...\n"); 

	while(1) {
		if (sem_trywait(&(self->parent_killswitch)) == 0) {
			printf("Leechthread dying...\n"); 
			break; 
		}
	}
}
