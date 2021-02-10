#include <fstream>
#include <iostream>
#include <cmath>


#include "matrix.h"

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

void round(Matrix& M, double accuracy)
{
    for (size_t i = 0; i < M.dim(); i++)
    {
        for (size_t j = 0; j < M.dim(); j++)
        {
            if (fabs(M[i][j]) < accuracy)
            {
                M[i][j] = 0.0;
            }
        }
    }
}

double* express_variables(Matrix A, double *b)
{
    double* solution = new double[A.dim()];
    double value;

    for (int i = A.dim() - 1; i >= 0; i--)
    {
        if (A[i][i] != 0)
        {
            value = b[i];

            for (size_t j = i + 1; j < A.dim(); j++)
            {
                value -= A[i][j] * solution[j];
            }

            solution[i] = value / A[i][i];
        }
        else
        {
            cout << "Can't solve (more than 1 solution or 0)." << endl;
            delete[] solution;

            return nullptr;
        }

    }

    return solution;
}

double getLength(double* b, size_t height) {
    return sqrt(scalar_product(b, b, height));
}

void print_vector(double* b, size_t height) {
    for (int i = 0; i < height; i++) {
		cout << b[i] << " " << endl;
    }

}
Matrix reflections(Matrix a, size_t i1) {
    Matrix tmp1(a.dim());
    tmp1 = a;

    for (int i = 0; i < i1; i++) {
        tmp1 = tmp1(0, 0);
    }

    double* b = new double[tmp1.dim()];

    for (int i = 0; i < tmp1.dim(); i++) {
        b[i] = tmp1[i][0];
    }

    double b_length = getLength(b, tmp1.dim());
    double* b_ac = new double[tmp1.dim()];

    for (int i = 1; i < tmp1.dim(); i++) {
        b_ac[i] = b[i];
    }

    b_ac[0] = b[0] - b_length;

   double b_b_ac = scalar_product(b_ac, b, tmp1.dim());

    double* w = new double[tmp1.dim()];

    for (int i = 0; i < tmp1.dim(); i++) {
        w[i] = b_ac[i] / sqrt(2 * b_b_ac);
    }

    Matrix uut(tmp1.dim());

    for (int i = 0; i < tmp1.dim(); i++) {
        for (int j = 0; j < tmp1.dim(); j++) {
            uut[i][j] = w[i] * w[j];
        }
    }

    Matrix E(tmp1.dim());
    E = E - 2 * uut;
    Matrix result(a.dim());

    size_t ei = 0;
    size_t ej = 0;

    for (int i = a.dim() - tmp1.dim(); i < a.dim(); i++) {
        for (int j = a.dim() - tmp1.dim(); j < a.dim(); j++) {
            result[i][j] = E[i - i1][j - i1];
        }
    }

    return result;
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
    delete[] b;

    return result;
}


int main() {
    //ifstream fout("input.txt");
   size_t height = 10;

    //fout >> height;
    Matrix a(height);
    a = generate_matrix_exp(height);
    //fout >> a;

    double* b = new double[height];
    b = generate_matrix_exp_b(a);

    //for (int i = 0; i < height; i++) {
    //    fout >> b[i];
    //}

    //fout.close();

    for (int i = 0; i < height - 1; i++) {
        Matrix U(height - i);
        U = reflections(a, i);
        a = U * a;
        b = multiply_b(U, b);
    }

    //round(a, pow(10, -9));

    double* solution = express_variables(a, b);
    print_vector(solution, a.dim());

    delete[] b;
    delete[] solution;

    return 0;

}
