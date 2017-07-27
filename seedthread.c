#include "headers/seedthread.h"

int Seedthread_init(Seedthread **seedthread, Arraylist *torrents)
{
	if (!(*seedthread = malloc(sizeof(Seedthread)))) {
		perror("Failed to allocate Seedthread\n"); 
		exit(0); 
	}

	(*seedthread)->torrents = torrents; 
	
	if (sem_init(&((*seedthread)->parent_killswitch), 0, 0) == -1) {
		perror("Failed to initialize Seedthread parent_killswitch\n"); 
		exit(0); 
	}

	pthread_create(&((*seedthread)->thread), NULL, &Seedthread_start, (void *) *seedthread);  	

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
		if (sem_trywait(&(self->parent_killswitch)) == 0) {
			printf("Seedthread dying...\n"); 
			break; 
		}
	}
}

int Seedthread_delete(void *seedthread)
{
	sem_destroy(&((((Seedthread *) seedthread))->parent_killswitch)); 
	free(seedthread); 
}
