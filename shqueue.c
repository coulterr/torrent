#include "headers/shqueue.h"

int Shqueue_init(Shqueue **shqueue)
{
	if (!(*shqueue = malloc(sizeof(Shqueue)))) {
		perror("Failed to allocate Shqueue\n"); 
		exit(0); 
	}

	(*shqueue)->head = NULL;
	(*shqueue)->tail = NULL; 
	(*shqueue)->size = 0; 

	if (!((*shqueue)->lock = malloc(sizeof(sem_t)))) {
		perror("Failed to allocate Shqueue lock\n"); 
		exit(0); 
	}	

	if (sem_init((*shqueue)->lock, 0, 1) == -1) {
		perror("Failed to initialize Shqueue lock\n"); 
		exit(0); 
	}
}

int Shqueue_push(Shqueue *shqueue, void *data)
{
	sem_wait(shqueue->lock); 
		
		struct Shqueue_node *node; 
		if (!(node = malloc(sizeof(struct Shqueue_node)))) {
			perror("Failed to allocate new Shqueue_node\n"); 
			exit(0); 
		}

		node->data = data; 
		node->next = NULL; 
		
		if (shqueue->size == 0) {
			shqueue->head = node; 
		}
		else {
			shqueue->tail->next = node; 
		}

		shqueue->tail = node; 
		shqueue->size = shqueue->size + 1; 
	
	sem_post(shqueue->lock); 
}


void *Shqueue_pop(Shqueue *shqueue) 
{
	void *data = NULL; 

	sem_wait(shqueue->lock); 

		if (shqueue->size > 0) {

			struct Shqueue_node *node = shqueue->head; 
			shqueue->head = node->next; 

			void *data = node->data; 
			free(node); 

			shqueue->size = shqueue->size - 1; 
		}
	
	sem_post(shqueue->lock); 

	return data; 
}

void *Shqueue_try_pop(Shqueue *shqueue) 
{
	void *data = NULL; 
	
	struct timespec t; 
	t.tv_sec = 30; 
	t.tv_nsec = 0; 

	if (sem_timedwait(shqueue->lock, &t)) {

		if (shqueue->size > 0) {

			struct Shqueue_node *node = shqueue->head; 
			shqueue->head = node->next; 

			data = node->data; 
			free(node); 

			shqueue->size = shqueue->size - 1; 
		}
	
		sem_post(shqueue->lock); 
	}

	return data; 
}


int Shqueue_delete(Shqueue *shqueue, int (*funcptr)(void *)) 
{
	struct Shqueue_node *node = shqueue->head; 
	while (node) 
	{
		if(funcptr == NULL) free(node->data); 
		else funcptr(node->data); 

		struct Shqueue_node *temp = node->next; 
		free(node); 
		node = temp; 
	}

	if(sem_destroy(shqueue->lock) == -1){
		perror("Failed to destroy Shqueue lock\n"); 
		exit(0); 
	}

	free(shqueue->lock); 
	free(shqueue); 
}
















