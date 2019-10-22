CC=g++

all: LinearAllocator

LinearAllocator: LinearAllocator.o
	$(CC) LinearAllocator.o -o LinearAllocator --std

LinearAllocator.o: LinearAllocator.cpp
	$(CC) -c LinearAllocator.cpp
clear:
	rm -rf *.o LinearAllocator
run:
	./LinAllocator

# test:
# 	python3 tests.py