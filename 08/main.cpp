#include <iostream>
#include "Threads.h"

using namespace std;
struct A {};

int foo(const A &) { return 100; }

int main() {
	Threads pool(8);
	
	auto task0 = pool.exec(foo, A());
	cout << task0.get() << endl;
	
	auto task1 = pool.exec([]() { return 1; });
	cout << task1.get() << endl;
	
	for (int i = 1; i < 16; i++) {
		cout << pool.exec([i]() { return i*i; }).get() << endl;
	}
    
    return 0;
}