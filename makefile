default: generator validator 

generator: generator.o bin_to_hex.o charlist.o
	gcc -o generator generator.o bin_to_hex.o charlist.o -lssl -lcrypto
validator: validator.o bin_to_hex.o segmentinfo.o fileinfo.o arraylist.o 
	gcc -o validator validator.o bin_to_hex.o segmentinfo.o fileinfo.o arraylist.o -lssl -lcrypto -lpthread
generator.o: generator.c
	gcc -c -o generator.o generator.c -std=gnu99
validator.o: validator.c headers/validator.h 
	gcc -c -o validator.o validator.c -std=gnu99
bin_to_hex.o: bin_to_hex.c headers/bin_to_hex.h
	gcc -c -o bin_to_hex.o bin_to_hex.c -std=gnu99
charlist.o: charlist.c headers/charlist.h
	gcc -c -o charlist.o charlist.c -std=gnu99
segmentinfo.o: segmentinfo.c headers/segmentinfo.h
	gcc -c -o segmentinfo.o segmentinfo.c -std=gnu99
fileinfo.o: fileinfo.c headers/fileinfo.h
	gcc -c -o fileinfo.o fileinfo.c -std=gnu99
arraylist.o: arraylist.c headers/arraylist.h
	gcc -c -o arraylist.o arraylist.c -std=gnu99
clean: 
	rm generator validator *.o
