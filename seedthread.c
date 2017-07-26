#include "headers/seedthread.h"

int Seedthread_init(Seedthread **seedthread, Arraylist *torrents)
{
	*seedthread = malloc(sizeof(Seedthread)); 
	(*seedthread)->torrents = torrents; 
	sem_init(&((*seedthread)->parent_killswitch), 0, 1); 
	pthread_create(&((*seedthread)->thread), NULL, &Seedthread_start, (void *) seedthread);  	

}

void *Seedthread_start(void *args)
{

}
