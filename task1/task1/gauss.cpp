#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <io.h>

void swap_row(double** matrix, int n, int m) {
	double* buffer = matrix[n];
	matrix[n] = matrix[m];
	matrix[m] = buffer;
}

int search_nonzero(double** matrix, int height, int n) {
	for (int i = n + 1; i < height; i++) {
		if (matrix[i][n]) {
			swap_row(matrix, n, i);
			return 0;
		}
	}
	printf("all 0");
	return 1;
}

void mult_num_row(double **matrix, int width, int row, double num) {
	for (int i = 0; i < width; i++) {
		matrix[row][i] *= num;
	}
}

// прибавляет к n m
void sum_rows(double** matrix, int width, int n, int m) {
	for (int i = 0; i < width; i++) {
		matrix[n][i] += matrix[m][i];
	}
}

double** upper_triangle(double** matrix, int height, int width) {
	for (int i = 0; i < height; i++) {
		if (!matrix[i][i]) {
			if (search_nonzero(matrix, height, i)) {
				continue;
			}
		}
		for (int j = i + 1; j < width -	1; j++) {
			if (!matrix[j][i]) {
				continue;
			}
			mult_num_row(matrix, width, i, -matrix[j][i] / matrix[i][i]);
			sum_rows(matrix, width, j, i);
		}
	}
	return matrix;
}