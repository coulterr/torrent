#include "headers/ipc_client.h"


int get_connection()
{
	int s, len; 
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

	return s; 
}


int send_message(int s, char *msg)
{
	int len; 
	
	if (send(s, msg, strlen(msg), 0) == -1){
		return -1; 
	}

	return 0; 	
}


int recv_message(char *buff, int s)
{
	int len; 

	if ((len = recv(s, buff, 1023, 0)) < 0) {
		return -1; 
	}else {
		buff[len] = '\0'; 
	}

	return 0; 
}

int close_connection(int s)
{
	if (close(s) == -1) return -1; 
	return 0;
}
