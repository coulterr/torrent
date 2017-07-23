#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdlib.h>
#include <semaphore.h>

typedef struct {
	
	void **data; 
	size_t size; 
	size_t capacity; 
	sem_t *lock; 

}Arraylist; 


int Arraylist_init(Arraylist **list);
size_t Arraylist_add(Arraylist *list, void *item);
void *Arraylist_get(Arraylist *list, size_t index);
int Arraylist_delete(Arraylist *list, int (*funcptr)(void *));

#endif
