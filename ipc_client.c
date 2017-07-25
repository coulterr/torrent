#include "headers/ipc_client.h"

int send_message(char *buff, char *msg)
{
	int s, t, len; 
	struct sockaddr_un remote; 

	if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		return -1; 
	}

	remote.sun_family = AF_UNIX; 
	strcpy(remote.sun_path, "./communication"); 
	len = strlen(remote.sun_path) + sizeof(remote.sun_family); 
	
	if (connect(s, (struct sockaddr *) &remote, len) == -1) {
		return -1; 
	}

	if (send(s, msg, strlen(msg), 0) == -1){
		return -1; 
	}

	if ((t=recv(s, buff, 1023, 0) > 0)) {
		return -1; 
	}else {
		buff[t] = '\0'; 
	}
	
	return 0; 	
}
