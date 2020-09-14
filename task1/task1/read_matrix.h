#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

double** allocate_matrix(int height, int width);

void free_matrix(double** matrix, int height);

double** read_matrix(int height, int width, FILE* input);
