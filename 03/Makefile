CC_OPTIONS = g++ -std=c++14

all: test

test: test.o matrix.o
	$(CC_OPTIONS) -o test matrix.o test.o

test.o: test.cpp
	$(CC_OPTIONS) -c -o test.o test.cpp

matrix.o: matrix.cpp
	$(CC_OPTIONS) -c -o matrix.o matrix.cpp

testing:
	./test

clear:
	rm -rf test *.o
	clear
