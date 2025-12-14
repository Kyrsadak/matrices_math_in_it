#ifndef DETERMINANT_H
#define DETERMINANT_H

#include "matrix.h"

// Determinant calculations
double det_sarrus_3x3(double** m);
double det_2x2(double** m);
double det_recursive(double** m, int n);
double det_lu(double** m, int n);

// LU decomposition
int lu_decompose(double** a, int n, int* perm, int* sign);

#endif // DETERMINANT_H