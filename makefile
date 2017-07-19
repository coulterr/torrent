default: generator validator 

generator: generator.o bin_to_hex.o
	g++ -o generator generator.o bin_to_hex.o -lssl -lcrypto
validator: validator.o bin_to_hex.o
	g++ -o validator validator.o bin_to_hex.o -lssl -lcrypto
generator.o: generator.cc headers/generator.h
	g++ -c -o generator.o generator.cc
validator.o: validator.cc headers/validator.h 
	g++ -c -o validator.o validator.cc
bin_to_hex.o: bin_to_hex.cc headers/bin_to_hex.h
	g++ -c -o bin_to_hex.o bin_to_hex.cc
clean: 
	rm generator validator *.o
