default: generator validator 

generator: generator.o bin_to_hex.o charlist.o
	gcc -o generator generator.o bin_to_hex.o charlist.o -lssl -lcrypto
validator: validator.o bin_to_hex.o charlist.o
	gcc -o validator validator.o bin_to_hex.o -lssl -lcrypto
generator.o: generator.c
	gcc -c -o generator.o generator.c -std=gnu99
validator.o: validator.c headers/validator.h 
	gcc -c -o validator.o validator.c -std=gnu99
bin_to_hex.o: bin_to_hex.c headers/bin_to_hex.h
	gcc -c -o bin_to_hex.o bin_to_hex.c -std=gnu99
charlist.o: charlist.c headers/charlist.h
	gcc -c -o charlist.o charlist.c -std=gnu99
clean: 
	rm generator validator *.o
