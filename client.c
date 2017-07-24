#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "headers/metainfo_parser.h"
#include "headers/torrentinfo.h"

int start_daemon(char *map_path)
{
	Arraylist *torrents; 
	Arraylist_init(&torrents); 

	get_meta_info(torrents, map_path); 
	for(size_t i = 0; i < torrents->size; i++){
		print_info(Arraylist_get(torrents, i)); 
	}

	Arraylist_delete(torrents, &Torrentinfo_delete); 
}


int main(int argc, char **argv)
{
	signal(SIGCHLD, SIG_IGN); 

	if (strcmp(argv[1], "start") == 0) {
		if (!fork()) {
			start_daemon(argv[2]); 
		}
	}
}
