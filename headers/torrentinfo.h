#ifndef TORRENTINFO_H
#define TORRENTINFO_H

#include <stdlib.h>


typedef struct {

	char meta_path[1024]; 
	char downloaded_segments[250000];

}Torrentinfo; 

int Torrentinfo_init(Torrentinfo **info);
int Torrentinfo_delete(Torrentinfo *info);

#endif
