generator_objs = generator.o hash_functions.o charlist.o
client_objs = client.o metainfo_parser.o hash_functions.o segmentinfo.o \
		fileinfo.o torrentinfo.o arraylist.o shqueue.o \
		ipc_server.o ipc_client.o seedthread.o leechthread.o \
		leech_control_thread.o leech_connection_thread.o

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
shqueue.o: shqueue.c headers/shqueue.h
	gcc -c -o shqueue.o shqueue.c -std=gnu99
ipc_server.o: ipc_server.c headers/ipc_server.h
	gcc -c -o ipc_server.o ipc_server.c -std=gnu99
ipc_client.o: ipc_client.c headers/ipc_client.h
	gcc -c -o ipc_client.o ipc_client.c -std=gnu99
seedthread.o: seedthread.c headers/seedthread.h
	gcc -c -o seedthread.o seedthread.c -std=gnu99
leechthread.o: leechthread.c headers/leechthread.h
	gcc -c -o leechthread.o leechthread.c -std=gnu99
leech_control_thread.o: leech_control_thread.c headers/leech_control_thread.h
	gcc -c -o leech_control_thread.o leech_control_thread.c -std=gnu99
leech_connection_thread.o: leech_connection_thread.c headers/leech_connection_thread.h
	gcc -c -o leech_connection_thread.o leech_connection_thread.c -std=gnu99


clean: 
	rm generator client *.o
