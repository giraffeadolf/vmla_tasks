#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <io.h>

int** allocate_matrix(int height, int width);

void free_matrix(int** matrix, int height);

int** read_matrix(int height, int width, FILE* input);
