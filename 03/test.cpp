#include <iostream>
#include <vector>
#include "matrix.h"
#include <string>
#include <unistd.h>

using std::cout;
using std::endl;
using std::vector;
using std::string;

int bad = 0;
int N = 1;
string s;

void startTest(string name) {
    s = name;
    if (N == 1) cout << "===========================================" << endl;
    cout << "Start test: " << N << " - " << s << endl;
    N++;
}

void endTest() {
    cout << "End test: " << N - 1 << endl;
    cout << "===========================================" << endl;
}

void ok() {
    cout << s << " -- OK" << endl;
}

void error() {
    bad++;
    cout << s << " -- ERROR" << endl;
}

void testResult() {
    N--;
    cout << (N - bad) << " / " << N << " passed" << endl;
}

int main(void) {

    Matrix m(5, 7);

//================================================================
    startTest("m[2][3] = 123");
    m[2][3] = 123;

    if (m[2][3] == 123) {
        ok();
    } else {
        error();
    }
    endTest();
//================================================================
    startTest("double x = m[2][3]");
    double x = m[2][3];
    if (x == 123) {
        ok();
    } else {
        error();
    }
    endTest();
//================================================================
    startTest("Compare two equal matrix");
    Matrix p(2, 2);
    p[0][0] = 1;
    p[0][1] = 2;
    p[1][0] = 3;
    p[1][1] = 4;

    Matrix p_copy(2, 2);
    p_copy[0][0] = 1;
    p_copy[0][1] = 2;
    p_copy[1][0] = 3;
    p_copy[1][1] = 4;

    if (p == p_copy && m != p) {
        ok();
    } else {
        error();
    }
    endTest();
//================================================================
    startTest("Assignment");
    m = p;
    if (m == p_copy) {
        ok();
    } else {
        error();
    }
    endTest();
//================================================================
    startTest("Multiply by number");
    m *= 5;
    if (m[0][0] == 5 && m[0][1] == 10 && m[1][0] == 15 && m[1][1] == 20) {
        ok();
    } else {
        error();
    }
    endTest();
//================================================================

    testResult();
    return 0;
}
