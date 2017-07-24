generator_objs = generator.o hash_functions.o charlist.o
client_objs = client.o metainfo_parser.o hash_functions.o segmentinfo.o \
		fileinfo.o torrentinfo.o arraylist.o 

default: generator client

generator: $(generator_objs)
	gcc -o generator $(generator_objs) -lssl -lcrypto
client: $(client_objs)
	gcc -o client $(client_objs) -lssl -lcrypto -lpthread
client.o: client.c 
	gcc -c -o client.o client.c -std=gnu99
generator.o: generator.c
	gcc -c -o generator.o generator.c -std=gnu99
metainfo_parser.o: metainfo_parser.c headers/metainfo_parser.h 
	gcc -c -o metainfo_parser.o metainfo_parser.c -std=gnu99
hash_functions.o: hash_functions.c headers/hash_functions.h
	gcc -c -o hash_functions.o hash_functions.c -std=gnu99
charlist.o: charlist.c headers/charlist.h
	gcc -c -o charlist.o charlist.c -std=gnu99
segmentinfo.o: segmentinfo.c headers/segmentinfo.h
	gcc -c -o segmentinfo.o segmentinfo.c -std=gnu99
fileinfo.o: fileinfo.c headers/fileinfo.h
	gcc -c -o fileinfo.o fileinfo.c -std=gnu99
torrentinfo.o: torrentinfo.c headers/torrentinfo.h
	gcc -c -o torrentinfo.o torrentinfo.c -std=gnu99
arraylist.o: arraylist.c headers/arraylist.h
	gcc -c -o arraylist.o arraylist.c -std=gnu99

clean: 
	rm generator client *.o
