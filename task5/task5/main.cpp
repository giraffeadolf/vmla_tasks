#include <fstream>
#include <iostream>

#include "matrix.h"
#include "inverse.h"

using namespace std;


double* solve(Matrix M, double* b)
{

}


int main()
{
    ifstream fout("input.txt");
    size_t height;

    fout >> height;
    Matrix a(height);
    fout >> a;

    double* b = new double[height];

    for (int i = 0; i < height; i++)
    {
        fout >> b[i];
    }

    fout.close();


    Matrix inversed;
    inversed = inverse(a);
    cout << inversed;


    delete[] b;
	return 0;
}
