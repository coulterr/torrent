#include "headers/arraylist.h"
#include "headers/fileinfo.h"
#include "headers/segmentinfo.h"
#include "headers/metainfo_parser.h"


int main(int argc, char **argv)
{
	Arraylist *files; 
	Arraylist *segments; 

	Arraylist_init(&files); 
	Arraylist_init(&segments); 
	
	get_meta_info(argv[1], files, segments); 

	Arraylist_clean(files, &Fileinfo_clean); 
	Arraylist_clean(segments, &Segmentinfo_clean); 



	//Arraylist_clean(list, &);

}

