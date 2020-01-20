CC = g++ -std=c++14


run: generate main check

generate: generate.cpp
	$(CC) generate.cpp -o generate 
	./generate 

main: %: %.cpp
	$(CC) $< -o $@ -pthread
	./main 

check: generate main
	$(CC) check.cpp -o check
	./check

clear:
	rm -f generate main check
	clear