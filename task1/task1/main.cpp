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

	int height;
	int width;
	fscanf(input, "%d %d", &height, &width);

	double **matrix = read_matrix(height, width, input);
	if (!matrix) {
		printf("Can't read matrix.");
		return 1;
	}

	upper_triangle(matrix, height, width);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			printf("%lf ", matrix[i][j]);
		}
		printf("\n");
	}

	fclose(input);

	free_matrix(matrix, height);

	return 0;
}