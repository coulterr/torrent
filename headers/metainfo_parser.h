#ifndef METAINFO_PARSER_H
#define METAINFO_PARSER_H


#include <sys/types.h>
#include <sys/stat.h>
#include <openssl/sha.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "bin_to_hex.h"
#include "segmentinfo.h"
#include "fileinfo.h"
#include "arraylist.h"

int read_line(char *buff, FILE *file);
int get_meta_info(const char *meta_path, Arraylist *files, Arraylist *segments);

#endif
