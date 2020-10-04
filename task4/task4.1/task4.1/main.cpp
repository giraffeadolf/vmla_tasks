#include <iostream>
#include <fstream>

#include "matrix.h"
#include "rotation_method.h"

using namespace std;


int main()
{
	ifstream input("input.txt");
	size_t dim;
	input >> dim;
	Matrix A(dim, input);

	double* b = new double[dim];

	for (size_t i = 0; i < dim; i++)
	{
		input >> b[i];
	}

	input.close();

	double* solution = rotate(A, b);

	cout << "Solutions: " << endl;

	for (size_t i = 0; i < A.dim(); i++)
	{
		cout << "x_" << i + 1 << ": " << solution[i] << endl;
	}

	delete[] solution;

	return EXIT_SUCCESS;
}
