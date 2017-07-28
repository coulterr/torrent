#include <stdlib.h>
#include <stdio.h>

#include "headers/shqueue.h"

int main(int argc, char **argv)
{
	Shqueue *shqueue; 
	Shqueue_init(&shqueue); 

	Shqueue_push(shqueue, "one"); 
	Shqueue_push(shqueue, "two"); 
	Shqueue_push(shqueue, "three"); 

	for (int i = 0; i < 3; i++) {
		char *word = (char *) Shqueue_pop(shqueue); 
		printf("%s\n", word); 
	}

}
