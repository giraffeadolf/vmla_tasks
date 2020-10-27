#include <iostream>
using namespace std;

#include "matrix.h"


double scalar_product(double* a, double* b, size_t height) {
    double sum = 0;
    for (int i = 0; i < height; i++) {
        sum += a[i] * b[i];
    }
    return sum;
}


double getLength(double* b, size_t height) {
    return sqrt(scalar_product(b, b, height));
}


double* iteration(Matrix A, double* x_prev, double mu)
{

}


double* solve(Matrix A)
{

}

