#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "read_matrix.h"
#include "square_root_method.h"
#include "run_method.h"

int main() {

	//FILE* input = fopen("input.txt", "r");
	//if (!input) {
	//	printf("Can't open file\n");
	//	return NULL;
	//}
	//
	//size_t height, width;
	//fscanf(input, "%zd %zd", &height, &width);
	//
	//if (height != width - 1)
	//{
	//	printf("Can't solve this.\n");
	//	return 0;
	//}
	//
	//double **matrix = read_matrix(height, width, input);
	//fclose(input);
	
	//if (!matrix) {
	//	printf("Can't read matrix.\n");
	//	return 1;
	//}

	//double *solutions = run_method_3(matrix, height);

	// ����� ����������� �����
	int height = 100;
	double** matrix = generate_matrix_exp(height);

	double** T = represent_as_product(matrix, height);
	double* solutions = solve(matrix, T, height);

	//size_t height = 10;
	//size_t width = height + 1;

	//double** matrix = generate_matrix_exp(height);

	//matrix = upper_triangle(matrix, height, width);
	//double* solution = express_variables(matrix, height, width);

	//if (!solution)
	//{
	//	return 0;
	//}

	//for (size_t i = 0; i < height; i++) {
	//	for (size_t j = 0; j < width; j++) {
	//		printf("%lf ", matrix[i][j]);
	//	}
	//	printf("\n");
	//}

	printf("Solutions:\n");
	for (size_t i = 0; i < height; i++)
	{
		printf("x%d = %lf\n", i + 1, solutions[i]);
	}
	
	free_matrix(matrix, height);
	delete[] solutions;

	return 0;
}