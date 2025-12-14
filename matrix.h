#ifndef MATRIX_H
#define MATRIX_H

#include "utils.h"

// Matrix allocation and deallocation
double** alloc_matrix(int n);
void free_matrix(double** m, int n);

// Matrix input/output
void read_matrix(double** m, int n);
void read_matrix_from_file(double** m, int n, const char* filename);
void print_matrix(double** m, int n);
void save_matrix_to_file(double** m, int n, const char* filename);

// Matrix operations
void copy_matrix(double** src, double** dst, int n);
void identity_matrix(double** m, int n);
void swap_rows(double** m, int n, int row1, int row2);

#endif // MATRIX_H