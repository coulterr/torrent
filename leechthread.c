#include "headers/leechthread.h"


int Leechthread_init(Leechthread **leechthread, Arraylist *torrents)
{
	*leechthread = malloc(sizeof(Leechthread)); 
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
	t.tv_nsec += 30000000000;
	t.tv_sec = t.tv_nsec / 1000000000;
	t.tv_nsec %= 1000000000;
	size_t index = 0; 

	Arraylist *leeches;
	Arraylist_init(&leeches); 


	while (1) {
	
		if (sem_timedwait(self->torrents->full, &t) == 0) {

			Torrentinfo *torrent = (Torrentinfo *) Arraylist_get(self->torrents, index); 
		
			Leech_control_thread *leech; 
			Leech_control_thread_init(&leech, torrent);

			Arraylist_add(leeches, leech); 
			
			index++; 
		}
		
		if (sem_trywait(&(self->parent_killswitch)) == 0) {
			
			printf("Leechthread dying...\n"); 
		
			for (size_t i = 0; i < leeches->size; i++) {
				Leech_control_thread *leech = Arraylist_get(leeches, i); 
				sem_post(&(leech->killswitch)); 
			}
	
			for (size_t i = 0; i < leeches->size; i++) {
				Leech_control_thread *leech = Arraylist_get(leeches, i); 
				pthread_join(leech->thread, NULL); 
			}
			
			break; 
		
		}
		
		continue; 
	}

	Arraylist_delete(leeches, &Leech_control_thread_delete); 
}
