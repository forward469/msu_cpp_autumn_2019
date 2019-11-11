CC_OPTIONS = g++ -std=c++14

all: BigInt run

BigInt: BigInteger.o
	$(CC_OPTIONS) -o BigInt BigInteger.o

BigInteger.o: BigInteger.cpp
	$(CC_OPTIONS) -c -o BigInteger.o BigInteger.cpp

run:
	./BigInt

clear:
	rm -rf BigInt *.o
	clear
