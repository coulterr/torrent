#include "headers/leechpair.h"

int Leechpair_init(Leechpair **pair, Segmentinfo *segment, Torrentinfo *torrent)
{
	*pair = malloc(sizeof(Leechpair)); 
	(*pair)->segment = segment; 
	(*pair)->torrent = torrent; 
}

int Leechpair_delete(void *pair)
{
	free(pair); 
}
