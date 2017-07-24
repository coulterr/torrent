#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include "headers/metainfo_parser.h"
#include "headers/torrentinfo.h"
#include "headers/listener.h"

int start_daemon(char *map_path)
{
	signal(SIGCHLD, SIG_IGN); 

	if (!fork()) {
	
		Arraylist *torrents; 
		Arraylist_init(&torrents); 

		get_meta_info(torrents, map_path); 
		
		for(size_t i = 0; i < torrents->size; i++){
			print_info(Arraylist_get(torrents, i)); 
		}

		pthread_t thread; 
		pthread_create(&thread, NULL, &start_listening, (void *) torrents); 
		pthread_join(thread, NULL); 

		Arraylist_delete(torrents, &Torrentinfo_delete); 
	}
}


int main(int argc, char **argv)
{
	if (strcmp(argv[1], "start") == 0) {
		start_daemon(argv[2]);
	}

}
