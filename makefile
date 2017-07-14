hash_test: hash_test.o bin_to_hex.o
	g++ -o hash_test hash_test.o bin_to_hex.o -lssl -lcrypto
bin_to_hex.o: bin_to_hex.cc bin_to_hex.h
	g++ -c -o bin_to_hex.o bin_to_hex.cc
hash_test.o: hash_test.cc
	g++ -c -o hash_test.o hash_test.cc

