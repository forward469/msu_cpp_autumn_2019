CC_OPTIONS = g++ -std=c++14

all: main run

main: main.o
	$(CC_OPTIONS) main.o -o  main

main.o: main.cpp
	$(CC_OPTIONS) -c main.cpp

clear:
	rm -rf *.o main
	clear
run:
	./main