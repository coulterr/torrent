#include "headers/leech_connection_thread.h"

int Leech_connection_thread_init(Leech_connection_thread **leech_connection_thread, Torrentinfo *torrent)
{
	*leech_connection_thread = malloc(sizeof(Leech_connection_thread)); 
	(*leech_connection_thread)->torrent = torrent; 

	pthread_create(&((*leech_connection_thread)->thread), NULL, &Leech_connection_thread_start, (void *) *leech_connection_thread); 
}


int Leech_connection_thread_delete(void *leech_connection_thread)
{
	free(leech_connection_thread); 
}

void *Leech_connection_thread_start(void *args)
{
	Leech_connection_thread *self = (Leech_connection_thread *) args; 
	printf("Leech connection thread started...\n"); 

	sleep(30); 
	printf("Leech connection thread dying...\n"); 
	

}
