#ifndef GENERATOR_H
#define GENERATOR_H

#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include <iostream>
#include <openssl/sha.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "bin_to_hex.h"

int main (int argc, char **argv);

#endif
