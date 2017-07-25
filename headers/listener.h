#ifndef LISTENER_H
#define LISTENER_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "arraylist.h"

void *start_listening(void *arg);

#endif
