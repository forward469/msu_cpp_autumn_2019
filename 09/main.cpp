#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <thread>
#include <algorithm>

using namespace std;

constexpr size_t MEMORY = 1024 * 1000;

vector<string> split(ifstream &f, uint64_t *buf) {
    size_t idx;

    f.seekg(0, f.end);
    size_t len = f.tellg() / sizeof(uint64_t);
    f.seekg(0, f.beg);

    size_t n_amo = ((size_t) ceil((float) len / MEMORY)) << 1;

    vector<string> names(n_amo);
    for (size_t i = 0; i <  n_amo; ++i) {
        names[i] = to_string(i);
    }

    while(!f.eof()) {
        f.read(reinterpret_cast<char *>(buf), MEMORY * sizeof(uint64_t));
        size_t read_sz = f.gcount() / sizeof(uint64_t);

        thread t1([buf, read_sz]() {
            sort(buf, buf + read_sz / 2);
        });

        thread t2([buf, read_sz]() {
            sort(buf + read_sz / 2, buf + read_sz);
        });
        t1.join();
        t2.join();

        ofstream f1(names[idx], ios::binary);
        if (!f1) {
            throw ofstream::failure(names[idx]);
        }

        ofstream f2(names[idx + 1], ios::binary);
        if (!f2) {
            throw ofstream::failure(names[idx + 1]);
        }

        f1.write(reinterpret_cast<const char *>(buf), sizeof(uint64_t) * read_sz / 2);
        f2.write(reinterpret_cast<const char *>(buf + read_sz / 2), sizeof(uint64_t) * read_sz / 2);
        f1.close();
        f2.close();
        idx += 2;
    }
    f.close();
    return names;
}

void merge(vector<string> &names, uint64_t* buf) {
    for (size_t i = 0; i < names.size() - 1; ++i) {
        ifstream f1(names[i], ios::binary);
        if (!f1) {
            throw(ifstream::failure(names[i]));
        }

        ifstream f2(names[i + 1], ios::binary);
        if (!f2) {
            throw(fstream::failure(names[i + 1]));
        }

        uint64_t cur;
        size_t idx = 0;

        f1.read(reinterpret_cast<char *>(&cur), sizeof(uint64_t));
        f2.seekg(0, f2.end);
        size_t len = f2.tellg() / sizeof(uint64_t);
        f2.seekg(0, f2.beg);
        f2.read(reinterpret_cast<char *>(buf), len * sizeof(uint64_t));
        f2.close();

        ofstream f2_o(names[i + 1], ios::binary);

        while(idx < len && !f1.eof()) {
            if (cur >= buf[idx]) {
                f2_o.write(reinterpret_cast<const char *>(&buf[idx]), sizeof(uint64_t));
                ++idx;
            }
            if (cur <= buf[idx]) {
                f2_o.write(reinterpret_cast<const char *>(&cur), sizeof(uint64_t));
                f1.read(reinterpret_cast<char *>(&cur), sizeof(uint64_t));
            }
        }

        if (f1.eof())
            f2_o.write(reinterpret_cast<const char *>(&buf[idx]), sizeof(uint64_t) * (len - idx));
        while (!f1.eof()) {
            f2_o.write(reinterpret_cast<const char *>(&cur), sizeof(uint64_t));
            f1.read(reinterpret_cast<char *>(&cur), sizeof(uint64_t));
        }
        f1.close();
        f2_o.close();
    }
}

void clean(vector<string> &names) {
    for_each(names.begin(), names.end() - 1, [](string & name) { remove(name.c_str());});
    rename(names.back().c_str(), "result.txt");
}

int main(const int argc, const char *argv[]) {

    ifstream input("in.txt", ios::binary);

    uint64_t * buf = new uint64_t[MEMORY];
    try {
        vector<string> names = split(input, buf);
        merge(names, buf);
        clean(names);
    
    } 

    catch (exception &e) 
    {
        cout << e.what() << endl;
        delete[] buf;
        return 1;
    }
    
    delete[] buf;
    return 0;
}