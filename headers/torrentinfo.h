#ifndef TORRENTINFO_H
#define TORRENTINFO_H

#include <stdlib.h>
#include <string.h>
#include "arraylist.h"
#include "fileinfo.h"
#include "segmentinfo.h"

typedef struct {

	char metapath[1024]; 
	char dirpath[1024];
	Arraylist *files;
	Arraylist *segments; 

}Torrentinfo; 

int Torrentinfo_init(Torrentinfo **info);
int Torrentinfo_delete(void *info);

#endif
