#include "headers/metainfo_parser.h"
#include "headers/torrentinfo.h"

int main(int argc, char **argv)
{
	//Torrentinfo *info; 
	//Torrentinfo_init(&info, argv[1], ""); 

	//get_torrent_meta_info(info); 

	//print_info(info); 

	//Torrentinfo_delete(info); 

	Arraylist *torrents; 
	Arraylist_init(&torrents); 

	get_meta_info(torrents, argv[1]); 
	for(size_t i = 0; i < torrents->size; i++){
		print_info(Arraylist_get(torrents, i)); 
	}

	Arraylist_delete(torrents, &Torrentinfo_delete); 
}

