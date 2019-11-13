CC_OPTIONS = g++ -std=c++14

all: Serializer run

Serializer: Serializer.o
	$(CC_OPTIONS) Serializer.o -o  Serializer

Serializer.o: Serializer.cpp
	$(CC_OPTIONS) -c Serializer.cpp

clear:
	rm -rf *.o Serializer
	clear
run:
	./Serializer