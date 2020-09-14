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

	int height, width;
	fscanf(input, "%d %d", &height, &width);

	double **matrix = read_matrix(height, width, input);
	fclose(input);

	if (!matrix) {
		printf("Can't read matrix.");
		return 1;
	}

	matrix = upper_triangle(matrix, height, width);
	double* solution = express(matrix, height, width);

	if (!solution)
	{
		return 0;
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			printf("%lf ", matrix[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < height; i++)
	{
		printf("%lf\n", solution[i]);
	}

	free_matrix(matrix, height);
	free(solution);

	return 0;
}