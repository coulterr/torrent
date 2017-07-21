#ifndef CHARLIST_H
#define CHARLIST_H

#include <string.h>
#include <stdlib.h>

typedef struct {
	size_t size; 
	size_t capacity;
	char *data; 
}Charlist; 

int Charlist_init(Charlist *charlist);
int Charlist_add(Charlist *charlist, char *item, size_t len);
const char *Charlist_tochars(Charlist *charlist);
void Charlist_delete(Charlist *charlist);

#endif
