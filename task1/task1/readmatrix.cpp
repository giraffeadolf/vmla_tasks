#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include "readmatrix.h"


int **allocate_matrix(int height, int width) {
	int** result = (int**)calloc(height, sizeof(int*));
	if (!result) {
		printf("error");
		return NULL;
	}
	for (int i = 0; i < height; i++) {
		result[i] = (int*)malloc(sizeof(int) * width);
		if (!result[i]) {
			printf("error");
			free_matrix(result, height);
			return NULL;
		}
	}
	return result;
}

void free_matrix(int** matrix, int height) {
	for (int i = 0; i < height; i++) {
		if (matrix[i]) {
			free(matrix[i]);
		}
	}
	free(matrix);
}

int **read_matrix(int height, int width, FILE *input) {
	int** matrix = allocate_matrix(height, width);
	if (!matrix) {
		printf("error");
		return NULL;
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			//if (eof(input)) {
			//	printf("error");
			//	return NULL;
			//}
			fscanf(input, "%d", &matrix[i][j]);
		}
	}
	return matrix;
}