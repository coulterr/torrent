#include "headers/ipc_server.h"

void *start_listening(void *arg)
{
	Arraylist *torrents = arg; 

	printf("Thread started...\n"); 

	unsigned int s, s2; 
	struct sockaddr_un local, remote; 
	int len; 

	s = socket(AF_UNIX, SOCK_STREAM, 0); 
	local.sun_family = AF_UNIX; 
	strcpy(local.sun_path, "./communication"); 
	unlink(local.sun_path); 
	len = strlen(local.sun_path) + sizeof(local.sun_family); 
	bind(s, (struct sockaddr *) &local, len); 

	listen(s, 5); 

	len = sizeof(struct sockaddr_un); 
	char buff[1024]; 
	
	while (s2 = accept(s, (struct sockaddr *) &remote, &len)) {
		len = recv(s2, buff, 100, 0); 
		buff[len] = '\0'; 
		if(strcmp(buff, "stop") == 0){
			close(s2); 
			break;
		}
		send(s2, buff, len, 0); 
		close(s2); 
	}

	close(s); 

}
