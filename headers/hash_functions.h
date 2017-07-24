#ifndef BIN_TO_HEX_H
#define BIN_TO_HEX_H

#include <string.h>
#include <stdio.h>
#include <openssl/sha.h>

enum {SHA1_HEX_LENGTH = 40}; 
enum {META_BLOCK_LENGTH = 16000}; 
enum {META_SEGMENT_LENGTH = 256}; 

void bin_to_hex (unsigned char *dest, unsigned char *source, size_t len);
void to_sha1_hex(unsigned char *hex, unsigned char *source, size_t len); 

#endif
