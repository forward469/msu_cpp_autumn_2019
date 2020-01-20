#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

int main() {
    ifstream f("result.txt", ios::binary);
    
    f.seekg(0, f.end);

    uint64_t len = f.tellg() / sizeof(uint64_t);
    f.seekg(0, f.beg);
    
    uint64_t *a = new uint64_t[len + 1];
    f.read(reinterpret_cast<char *>(a), len * sizeof(uint64_t));

    cout << (is_sorted(a, a + len) ? "File is sorted.\n" : "File is not sorted.\n");
    delete[] a;
    f.close();
    return 0;
}