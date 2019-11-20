CC_OPTIONS = g++ -std=c++14

all: Format run

Format: Format.o
	$(CC_OPTIONS) Format.o -o  Format

Format.o: Format.cpp
	$(CC_OPTIONS) -c Format.cpp

clear:
	rm -rf *.o Format
	clear
run:
	./Format