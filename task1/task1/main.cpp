#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "readmatrix.h"

int main() {

	FILE* input = fopen("input.txt", "r");
	if (input == NULL) {
		printf("Can't open file");
		return NULL;
	}

	int height;
	int width;
	fscanf(input, "%d %d", &height, &width);

	int **matrix = read_matrix(height, width, input);
	if (!matrix) {
		printf("error");
		return 1;
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}

	fclose(input);

	free_matrix(matrix, height);

	return 0;
}