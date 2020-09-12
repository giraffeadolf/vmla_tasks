#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include "readmatrix.h"


double **allocate_matrix(int height, int width) {
	double** result = (double**)calloc(height, sizeof(double*));
	if (!result) {
		printf("error");
		return NULL;
	}
	for (int i = 0; i < height; i++) {
		result[i] = (double*)malloc(sizeof(double) * width);
		if (!result[i]) {
			printf("error");
			free_matrix(result, height);
			return NULL;
		}
	}
	return result;
}

void free_matrix(double** matrix, int height) {
	for (int i = 0; i < height; i++) {
		if (matrix[i]) {
			free(matrix[i]);
		}
	}
	free(matrix);
}

double **read_matrix(int height, int width, FILE *input) {
	double** matrix = allocate_matrix(height, width);
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
			fscanf(input, "%lf", &matrix[i][j]);
		}
	}
	return matrix;
}