#include <iostream>
#include "timer.hpp"
using namespace std;

int sum_by_rows()
{
    const int M=20000;

    int* arr = (int*) malloc(M * M * sizeof(int));
    using Matrix = int (*)[M];
    Matrix m = (Matrix) arr;

    for(int i=0; i<M; i++){
        for(int j=0; j<M; j++){
            m[i][j] = 0;
        };
    };

    int sum=0;
    for(int i=0; i<M; i++){
        for(int j=0; j<M; j++){
            sum += m[i][j];
        }
    }
    return sum;
}

int main()
{
    cout << "Time for sum by rows : " << endl;
    Timer t1;
    for(int i=0; i<10; i++){
        sum_by_rows();
    }
    return 0;
}