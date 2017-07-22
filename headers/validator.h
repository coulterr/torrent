#ifndef VALIDATOR_H
#define VALIDATOR_H


#include <sys/types.h>
#include <sys/stat.h>
#include <openssl/sha.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "bin_to_hex.h"

void print_hash(unsigned char *hash);
int main (int argc, char **argv);

#endif
