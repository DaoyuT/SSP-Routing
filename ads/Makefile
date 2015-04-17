CC = g++ -w -Wno-deprecated 

tag = -i

src = ./src
bin = ./bin

ifdef linux
tag = -n
endif

ssp: ssp.o
	$(CC) -o $(bin)/ssp $(bin)/ssp.o

routing: routing.o BinaryTrie.o
	$(CC) -o $(bin)/routing $(bin)/routing.o $(bin)/BinaryTrie.o

ssp.o: $(src)/ssp.cpp
	$(CC) -o $(bin)/ssp.o -g -std=c++11 -c $(src)/ssp.cpp

routing.o: $(src)/routing.cpp
	$(CC) -o $(bin)/routing.o -g -std=c++11 -c $(src)/routing.cpp

BinaryTrie.o: $(src)/BinaryTrie.cpp
	$(CC) -o $(bin)/BinaryTrie.o -g -std=c++11 -c $(src)/BinaryTrie.cpp

clean:
	rm -f $(bin)/*.exe 
	rm -f $(bin)/*.o
