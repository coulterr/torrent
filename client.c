#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include "headers/metainfo_parser.h"
#include "headers/torrentinfo.h"
#include "headers/listener.h"

int get_torrent_data(char *map_path)
{
	Arraylist *torrents; 
	Arraylist_init(&torrents); 

	if (get_meta_info(torrents, map_path) == -1) {
		fprintf(stderr, "Failed to parse metainfo\n"); 
		exit(0); 
	}
	
	for(size_t i = 0; i < torrents->size; i++){
		print_info(Arraylist_get(torrents, i)); 
	}

	pthread_t thread; 
	pthread_create(&thread, NULL, &start_listening, (void *) torrents); 
	pthread_join(thread, NULL); 

	Arraylist_delete(torrents, &Torrentinfo_delete); 
}


int start_daemon(char *map_path)
{
	signal(SIGCHLD, SIG_IGN); 

	switch (fork()) {
		case 0:
			get_torrent_data(map_path); 
			return 0; 

		case -1:
			return -1; 

		default: 
			return 1;

	}
}


int main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "Not enough arguments\n"); 
		exit(0); 
	}

	if (strcmp(argv[1], "start") == 0) 
	{
		if(argc < 3) {
			fprintf(stderr, "Expected: start $mapfile_path\n"); 
			exit(0); 
		}

		if (start_daemon(argv[2]) == -1) {
			fprintf(stderr, "Failed to fork process.\n"); 
			exit(0); 
		}
	}
	
	else if (strcmp(argv[1], "add") == 0)
	{
		if(argc < 4) {
			fprintf(stderr, "Expected: add $metafile_path $rootdir\n"); 
			exit(0); 
		}
	}	
	
	else if(strcmp(argv[1], "help") == 0)
	{
		//print help
	}
	
	else
	{
		fprintf(stderr, "Invalid command"); 
	}

}
