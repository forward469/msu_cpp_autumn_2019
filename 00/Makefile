CC=g++

all: sum_by_rows sum_by_cols run

sum_by_rows: sum_by_rows.o
	$(CC) sum_by_rows.o -o sum_by_rows --std=c++11 -O2
sum_by_cols: sum_by_cols.o
	$(CC) sum_by_cols.o -o sum_by_cols --std=c++11 -O2

sum_by_rows.o: sum_by_rows.cpp
	$(CC) -c sum_by_rows.cpp
sum_by_cols.o: sum_by_cols.cpp
	$(CC) -c sum_by_cols.cpp

clear:
	rm -rf *.o sum_by_rows sum_by_cols
run:
	./sum_by_rows
	./sum_by_cols