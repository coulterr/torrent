#include "headers/torrentinfo.h"


int Torrentinfo_init(Torrentinfo **info, const char *metapath, const char *dirpath)
{
	*info = malloc(sizeof(Torrentinfo)); 
	Arraylist_init(&((*info)->files)); 
	Arraylist_init(&((*info)->segments)); 
	strcpy((*info)->metapath, metapath); 
	strcpy((*info)->dirpath, dirpath); 

}


int Torrentinfo_delete(Torrentinfo *info)
{
	Arraylist_delete(info->files, &Fileinfo_delete); 
	Arraylist_delete(info->segments, &Segmentinfo_delete);
	free(info); 
}
