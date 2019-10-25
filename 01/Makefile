CC=g++

all: calc test

calc: calc.o
	$(CC) calc.o -o calc --std=c++11 -O2
calc.o: calc.cpp
	$(CC) -c calc.cpp
clear:
	rm -rf *.o calc
	clear
run:
	./calc
test:
	python3 tests.py