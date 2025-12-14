#ifndef MINORS_H
#define MINORS_H

#include "matrix.h"
#include "determinant.h"

// Minor and cofactor calculations
double minor_at(double** a, int n, int row, int col);
double cofactor_at(double** a, int n, int row, int col);
void cofactor_matrix(double** a, double** cof, int n);

#endif // MINORS_H