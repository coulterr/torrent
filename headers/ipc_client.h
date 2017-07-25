#ifndef IPC_CLIENT_H
#define IPC_CLIENT_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "arraylist.h"

int get_connection(); 
int send_message(int s, char *msg); 
int recv_message(char *buff, int s); 
int close_connection(int s); 

#endif
