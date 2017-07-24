#include "headers/metainfo_parser.h"
#include "headers/torrentinfo.h"

int main(int argc, char **argv)
{
	Torrentinfo *info; 
	Torrentinfo_init(&info, argv[1], ""); 

	get_meta_info(info); 

	print_info(info); 

	Torrentinfo_delete(info); 
}

