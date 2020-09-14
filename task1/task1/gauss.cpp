#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void swap_rows(double** matrix, int n, int m) {
	double* buffer = matrix[n];
	matrix[n] = matrix[m];
	matrix[m] = buffer;
}

int search_nonzero(double** matrix, int height, int n) {
	for (int i = n + 1; i < height; i++) {
		if (matrix[i][n]) {
			swap_rows(matrix, n, i);
			return 0;
		}
	}

	printf("all 0");
	return 1;
}

void multiple_row_by_number(double **matrix, int width, int row, double num) {
	for (int i = 0; i < width; i++) {
		matrix[row][i] *= num;
	}
}

// прибавляет строку с номером n к строке с номером m
void sum_rows(double** matrix, int width, int n, int m) {
	for (int i = 0; i < width; i++) {
		matrix[n][i] += matrix[m][i];
	}
}

double** upper_triangle(double** matrix, int height, int width) {
	for (int i = 0; i < height; i++) {
		if (!matrix[i][i] && search_nonzero(matrix, height, i)) {
			continue;
		}

		for (int j = i + 1; j < width -	1; j++) {
			if (!matrix[j][i]) {
				continue;
			}

			multiple_row_by_number(matrix, width, i, -matrix[j][i] / matrix[i][i]);
			sum_rows(matrix, width, j, i);
		}
	}

	return matrix;
}


double* express(double** matrix, int height, int width)
{
	double* solution = (double*)malloc((width - 1) * sizeof(double));
	double value;

	if (!solution)
	{
		printf("Can't allocate memory for solution");
		return NULL;
	}

	// guess that height == width - 1

	for (int i = height - 1; i >= 0; i--)
	{
		if (matrix[i][i] != 0)
		{
			value = matrix[i][width - 1];

			for (int j = i + 1; j < width - 1; j++)
			{
				value -= matrix[i][j] * solution[j];
			}

			solution[i] = value / matrix[i][i];
		}
		else
		{
			printf("Can't solve (more than 1 solution or 0).");
			free(solution);
			
			return NULL;
		}

	}

	return solution;
}
