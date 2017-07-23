#include "headers/arraylist.h"

int Arraylist_init(Arraylist **list)
{
	*list = malloc(sizeof(Arraylist)); 
	(*list)->size = 0; 
	(*list)->capacity = 100; 
	(*list)->data = malloc(sizeof(void *) * 100); 
	(*list)->lock = malloc(sizeof(sem_t)); 
	sem_init((*list)->lock, 0, 1); 
}

size_t Arraylist_add(Arraylist *list, void *item)
{
	if (list->size == list->capacity)
	{
		list->capacity = list->capacity * 2; 
		list->data = realloc(list->data, sizeof(void *) * list->capacity); 
	}

	(list->data)[list->size] = item; 
	list->size = list->size + 1; 
	return (list->size) - 1;  
}

void *Arraylist_get(Arraylist *list, size_t index)
{
	if (index >= 0 && index < list->size) return (list->data)[index]; 
	return NULL; 	
}

int Arraylist_clean(Arraylist *list, int (*funcptr)(void *))
{
	for (size_t i = 0; i < list->size; i++){
		(*funcptr) ((list->data)[i]); 
	}
	
	free(list->lock); 
	free(list->data); 
	free(list); 
}


