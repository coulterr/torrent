#ifndef LEECHPAIR_H
#define LEECHPAIR_H


#include <stdlib.h>
#include "segmentinfo.h"
#include "torrentinfo.h"


typedef struct {
	
	Segmentinfo *segment; 
	Torrentinfo *torrent; 

}Leechpair; 

int Leechpair_init(Leechpair **pair, Segmentinfo *segment, Torrentinfo *torrent);
int Leechpair_delete(void *pair);

#endif
