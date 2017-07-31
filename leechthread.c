#include "headers/leechthread.h"


int Leechthread_init(Leechthread **leechthread, Arraylist *torrents)
{
	*leechthread = malloc(sizeof(leechthread)); 
	sem_init(&((*leechthread)->parent_killswitch), 0, 0);
	(*leechthread)->torrents = torrents; 

	pthread_create(&((*leechthread)->thread), NULL, &Leechthread_start, (void *) *leechthread); 
}


int Leechthread_kill(Leechthread *leechthread)
{
	sem_post(&(leechthread->parent_killswitch)); 
}

int Leechthread_delete(Leechthread *leechthread)
{
	sem_destroy(&(leechthread->parent_killswitch)); 

	free(leechthread); 
}

void *Leechthread_start(void *args)
{
	Leechthread *self = (Leechthread *) args; 

	printf("Leechthread started...\n"); 
	
	struct timespec t; 
	t.tv_sec = 30; 
	t.tv_nsec = 30000000000; 

	size_t index = 0; 


	while(1) {
	
		if (sem_timedwait(self->torrents->full, &t) == 0) {

			Torrentinfo *torrent = (Torrentinfo *) Arraylist_get(self->torrents, index); 
			
			for (size_t j = 0; j < torrent->segments->size; j++) {	
				
				Segmentinfo *segment = (Segmentinfo *) Arraylist_get(torrent->segments, j); 
				Fileinfo *file = (Fileinfo *) Arraylist_get(torrent->files, segment->file_index); 
				
				printf("PATH: %s\n", file->path); 
				printf("OFFSET: %s\n", segment->offset);
				
			} 
			
			
			//Do stuff with torrent	
			
			index++; 
		}
		
		if (sem_trywait(&(self->parent_killswitch)) == 0) {
			printf("Leechthread dying...\n"); 
			break; 
		}
		continue; 
	}
}
