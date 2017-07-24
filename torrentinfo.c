#include "headers/torrentinfo.h"


int Torrentinfo_init(Torrentinfo **info)
{
	*info = malloc(sizeof(Torrentinfo)); 
	Arraylist_init(&((*info)->files)); 
	Arraylist_init(&((*info)->segments)); 
}


int Torrentinfo_delete(void *info)
{
	Arraylist_delete(((Torrentinfo *)info)->files, &Fileinfo_delete); 
	Arraylist_delete(((Torrentinfo *)info)->segments, &Segmentinfo_delete);
	free(info); 
}
