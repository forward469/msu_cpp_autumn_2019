CC_OPTIONS = g++ -std=c++14

all: Vector run

Vector: Vector.o
	$(CC_OPTIONS) Vector.o -o  Vector

Vector.o: Vector.cpp
	$(CC_OPTIONS) -c Vector.cpp

clear:
	rm -rf *.o Vector
	clear
run:
	./Vector