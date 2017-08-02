#include "headers/leech_control_thread.h"

int Leech_control_thread_init(Leech_control_thread **leech_control_thread, Torrentinfo *torrent)
{
	*leech_control_thread = malloc(sizeof(Leech_control_thread)); 
	sem_init(&((*leech_control_thread)->killswitch), 0, 0);
	(*leech_control_thread)->torrent = torrent; 

	pthread_create(&((*leech_control_thread)->thread), NULL, &Leech_control_thread_start, (void *) *leech_control_thread); 
}


int Leech_control_thread_kill(Leech_control_thread *leech_control_thread)
{
	sem_post(&(leech_control_thread->killswitch)); 
}

int Leech_control_thread_delete(void *leech_control_thread)
{
	sem_destroy(&(((Leech_control_thread *) leech_control_thread)->killswitch)); 
	free(leech_control_thread); 
}

void *Leech_control_thread_start(void *args)
{
	Leech_control_thread *self = (Leech_control_thread *) args; 
	printf("Leech control thread started...\n"); 
	
	Arraylist *segments = self->torrent->segments; 
	Arraylist *files = self->torrent->files; 

	for (size_t i = 0; i < segments->size; i++) {
		
		Segmentinfo *segment = Arraylist_get(segments, i); 
		size_t file_index = segment->file_index; 
		
		Fileinfo *file = Arraylist_get(files, file_index); 

		printf("Segment Offset: %i\n", segment->offset); 
		printf("Path: %s\n", file->path); 
	}
	
	struct timespec t; 
	t.tv_nsec += 30000000000;
	t.tv_sec = t.tv_nsec / 1000000000;
	t.tv_nsec %= 1000000000;
	size_t index = 0; 

	Arraylist *connections; 
	Arraylist_init(&connections); 

	sem_t temp; 
	sem_init(&temp, 0, 10); 
	
	while (1) {
		
		//Start threads
		if(sem_trywait(&temp) == 0) {
			Leech_connection_thread *connection; 
			Leech_connection_thread_init(&connection, self->torrent); 
			Arraylist_add(connections, connection); 
		}

		if (sem_trywait(&(self->killswitch)) == 0) {
			printf("Leech control thread dying...\n"); 
			break; 
		}

	}

	
	for (size_t i = 0; i < connections->size; i++) {
		Leech_connection_thread *connection = (Leech_connection_thread *) Arraylist_get(connections, i); 
		pthread_join(connection->thread, NULL); 
	}

	printf("Leech control thread death finalized.\n"); 
	Arraylist_delete(connections, &Leech_connection_thread_delete); 

}
