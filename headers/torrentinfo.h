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
	char downloaded_segments[250000];
	Arraylist *files;
	Arraylist *segments; 

}Torrentinfo; 

int Torrentinfo_init(Torrentinfo **info, const char *metapath, const char *dirpath);
int Torrentinfo_delete(Torrentinfo *info);

#endif
