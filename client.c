#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include "headers/metainfo_parser.h"
#include "headers/torrentinfo.h"
#include "headers/ipc_server.h"
#include "headers/ipc_client.h"
#include "headers/seedthread.h"
#include "headers/leechthread.h"

int initialize_client(char *map_path)
{
	Arraylist *torrents; 
	Arraylist_init(&torrents); 

	if (get_meta_info(torrents, map_path) == -1) {
		perror("Failed to parse metainfo\n"); 
		exit(0); 
	}

	for(size_t i = 0; i < torrents->size; i++){
		print_info(Arraylist_get(torrents, i)); 
	}

	Seedthread *seedthread; 
	Seedthread_init(&seedthread, torrents); 

	Leechthread *leechthread; 
	Leechthread_init(&leechthread, torrents); 

	pthread_t ipc_thread; 
	pthread_create(&ipc_thread, NULL, &start_listening, (void *) torrents); //and shqueue
	pthread_join(ipc_thread, NULL);

	printf("Killing seedthread...\n"); 
	Seedthread_kill(seedthread); 
	printf("Killing leechthread...\n"); 
	Leechthread_kill(leechthread); 

	pthread_join(seedthread->thread, NULL); 
	pthread_join(leechthread->thread, NULL); 


	Seedthread_delete(seedthread); 
	Leechthread_delete(leechthread); 

	dump_to_map(map_path, torrents); 
	Arraylist_delete(torrents, &Torrentinfo_delete); 
}


int start_daemon(char *map_path)
{
	signal(SIGCHLD, SIG_IGN); 

	switch (fork()) {
		case 0:
			initialize_client(map_path); 
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
		perror("Not enough arguments\n"); 
		exit(0); 
	}

	if (strcmp(argv[1], "start") == 0) 
	{
		if(argc < 3) {
			perror("Expected: start $mapfile_path\n"); 
			exit(0); 
		}

		if (start_daemon(argv[2]) == -1) {
			perror("Failed to fork process.\n"); 
			exit(0); 
		}
	}
	
	else if (strcmp(argv[1], "add") == 0)
	{
		if(argc < 4) {
			perror("Expected: add $metafile_path $rootdir\n"); 
			exit(0); 
		}
	}	
	
	else if(strcmp(argv[1], "help") == 0)
	{
		//print help
	}

	else if (strcmp(argv[1], "test") == 0) 
	{
		char buff[1024]; 
		int s;
		if((s  = get_connection()) == -1){
			perror("Failed to get connection\n"); 
			exit(0); 
		}

		send_message(s, argv[2]); 
		recv_message(buff, s); 
		close_connection(s); 
		printf("response: %s\n", buff); 
	}
	
	else
	{
		perror("Invalid command"); 
	}

}
