#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdlib.h>

typedef struct {
	
	void **data; 
	size_t size; 
	size_t capacity; 

}Arraylist; 


int Arraylist_init(Arraylist **list);
size_t Arraylist_add(Arraylist *list, void *item);
void *Arraylist_get(Arraylist *list, size_t index);
int Arraylist_clean(Arraylist *list, int (*funcptr)(void *));

#endif
