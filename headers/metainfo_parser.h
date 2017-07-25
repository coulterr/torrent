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

#include "segmentinfo.h"
#include "hash_functions.h"
#include "fileinfo.h"
#include "arraylist.h"
#include "torrentinfo.h"

void print_info(Torrentinfo *info); 
int read_line(unsigned char *buff, FILE *file);
int get_torrent_meta_info(Torrentinfo *info); 
int get_meta_info(Arraylist *torrents, char *map_path);
int dump_to_map(char *map_path, Arraylist *torrents); 

#endif
