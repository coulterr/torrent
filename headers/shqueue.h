#ifndef SHQUEUE_H
#define SHQUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>


typedef struct {

	struct Shqueue_node *head; 
	struct Shqueue_node *tail; 
	size_t size; 
	sem_t *lock; 

}Shqueue;


struct Shqueue_node {
	
	void *data; 
	struct Shqueue_node *next; 
};

int Shqueue_init(Shqueue **shqueue);
int Shqueue_push(Shqueue *shqueue, void *data);
void *Shqueue_pop(Shqueue *shqueue);
int Shqueue_delete(Shqueue *shqueue, int (*funcptr)(void *));

#endif
