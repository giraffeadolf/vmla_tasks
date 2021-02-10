#include <fstream>
#include <iostream>

#include "matrix.h"
#include "inverse.h"

using namespace std;

Matrix generate_matrix_exp(size_t height) {
    double alpha = 10;

    Matrix matrix(height);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < height; j++) {
            matrix[i][j] = exp(-alpha * abs((i - j) * (i - j)));

        }
    }

    return matrix;
}

double* generate_matrix_exp_b(Matrix m) {

    double* b = new double[m.dim()];
    for (int i = 0; i < m.dim(); i++) {
        b[i] = 0;
        for (int j = 0; j < m.dim(); j++) {
            b[i] += m[i](j);
        }
    }

    return b;
}

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

double* multiply_b(Matrix M, double* b)
{
    double* result = new double[M.dim()];

    for (size_t i = 0; i < M.dim(); i++)
    {
        result[i] = 0.0;

        for (size_t j = 0; j < M.dim(); j++)
        {
            result[i] += M[i](j) * b[j];
        }
    }

    return result;
}


double* iteration(Matrix M, Matrix inversed, double* x_prev, double* b) 
{
    double* Ax_prev = multiply_b(M, x_prev);

    for (size_t k = 0; k < M.dim(); k++)
    {
        Ax_prev[k] -= b[k];
    }

    double* tmp = multiply_b(inversed, Ax_prev);

    for (size_t i = 0; i < M.dim(); i++)
    {
        x_prev[i] -= tmp[i];
    }

    delete[] Ax_prev;
    delete[] tmp;

    return x_prev;
}


double* copy_vector(double* vector, size_t height)
{
    double* result = new double[height];

    for (size_t i = 0; i < height; i++)
    {
        result[i] = vector[i];
    }

    return result;
}


double* solve(Matrix M, double* b)
{
    Matrix L = M;
    Matrix D = M;

    for (size_t i = 0; i < M.dim(); i++)
    {
        for (size_t j = 0; j < M.dim(); j++)
        {
            if (i <= j)
            {
                L[i][j] = 0;
            }

            if (i != j)
            {
                D[i][j] = 0;
            }
        }
    }

    Matrix D_L_inversed;
    Matrix tmp;
    tmp = D - L;
    D_L_inversed = inverse(tmp);

    double* x = new double[M.dim()];
    for (size_t i = 0; i < M.dim(); i++)
    {
        x[i] = 1;
    }

    double epsilon = pow(10, -9);

    while (true)
    {
        double* x_copy = copy_vector(x, M.dim());
        x = iteration(M, D_L_inversed, x, b);

        for (size_t j = 0; j < M.dim(); j++)
        {
            x_copy[j] -= x[j];
        }
        double length = getLength(x_copy, M.dim());

        if (length < epsilon)
        {
            break;
        }
    }

    return x;
}


int main()
{
    //ifstream fout("input.txt");
    size_t height = 5;

    //fout >> height;
    Matrix a(height);
    a = generate_matrix_exp(height);
    //fout >> a;

    double* b = new double[height];
    b = generate_matrix_exp_b(height);

    /*for (int i = 0; i < height; i++)
    {
        fout >> b[i];
    }

    fout.close();*/

    double * solution = solve(a, b);
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        cout << solution[i] << endl;
    }
    //cout << inverse(a);

    delete[] b;
    delete[] solution;
	return 0;
}
