#include "headers/arraylist.h"

int Arraylist_init(Arraylist **list)
{
	if(!(*list = malloc(sizeof(Arraylist)))){
		perror("Failed to allocate Arraylist\n");
		exit(0); 
	}

	(*list)->size = 0; 
	(*list)->capacity = 100; 
	
	if(!((*list)->data = malloc(sizeof(void *) * 100))){
		perror("Failed to allocate Arraylist data\n");
		exit(0); 
	}

	if(!((*list)->lock = malloc(sizeof(sem_t)))){
		perror("Failed to allocate Arraylist lock\n"); 
		exit(0); 
	}

	if(sem_init((*list)->lock, 0, 1) == -1){
		perror("Failed to initialize Arraylist lock\n"); 
		exit(0); 
	}
}

size_t Arraylist_add(Arraylist *list, void *item)
{
	sem_wait(list->lock); 

		if (list->size == list->capacity)
		{
			list->capacity = list->capacity * 2; 
			if(!(list->data = realloc(list->data, sizeof(void *) * list->capacity))){
				fprintf(stderr, "Failed to reallocate Arraylist data\n"); 
				exit(0); 
			}
		}

		(list->data)[list->size] = item; 
		list->size = list->size + 1;
		size_t result = (list->size) - 1;  
	
	sem_post(list->lock); 

	return result; 
}

void *Arraylist_get(Arraylist *list, size_t index)
{
	void *result = NULL;
	
	sem_wait(list->lock); 

		if (index >= 0 && index < list->size) result = (list->data)[index]; 

	sem_post(list->lock); 	

	return result; 
}

int Arraylist_delete(Arraylist *list, int (*funcptr)(void *))
{
	for (size_t i = 0; i < list->size; i++){
		(*funcptr) ((list->data)[i]); 
	}
	
	if(sem_destroy(list->lock) == -1){
		perror("Failed to destroy Arraylist lock\n"); 
		exit(0); 
	}

	free(list->lock); 
	free(list->data); 
	free(list); 
}


