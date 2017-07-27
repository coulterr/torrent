#include "headers/seedthread.h"

int Seedthread_init(Seedthread **seedthread, Arraylist *torrents)
{
	*seedthread = malloc(sizeof(Seedthread)); 
	(*seedthread)->torrents = torrents; 
	sem_init(&((*seedthread)->parent_killswitch), 0, 1); 
	pthread_create(&((*seedthread)->thread), NULL, &Seedthread_start, (void *) seedthread);  	

}


int Seedthread_kill(Seedthread *seedthread)
{
	sem_post(&(seedthread->parent_killswitch)); 
}


void *Seedthread_start(void *args)
{
	Seedthread *self = (Seedthread *) args; 

	printf("Seedthread started...\n"); 
	
	while(1) {
		if (sem_trywait(&(self->parent_killswitch))) {
			printf("Seedthread dying...\n"); 
		}
	}
}

int Seedthread_delete(void *seedthread)
{
	sem_destroy(&((((Seedthread *) seedthread))->parent_killswitch)); 
	free(seedthread); 
}
