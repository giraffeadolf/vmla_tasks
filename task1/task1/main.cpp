#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "read_matrix.h"
#include "gauss.h"

int main() {

	FILE* input = fopen("input.txt", "r");
	if (!input) {
		printf("Can't open file");
		return NULL;
	}

	size_t height, width;
	fscanf(input, "%zd %zd", &height, &width);
	printf("%zd %zd", height, width);
	
	if (height != width - 1)
	{
		printf("Can't solve this.");
		return 0;
	}

	double **matrix = read_matrix(height, width, input);
	fclose(input);

	if (!matrix) {
		printf("Can't read matrix.");
		return 1;
	}

	matrix = upper_triangle(matrix, height, width);
	double *solution = express_variables(matrix, height, width);

	if (!solution)
	{
		return 0;
	}

	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			printf("%lf ", matrix[i][j]);
		}
		printf("\n");
	}

	for (size_t i = 0; i < height; i++)
	{
		printf("%lf\n", solution[i]);
	}

	free_matrix(matrix, height);
	free(solution);

	return 0;
}