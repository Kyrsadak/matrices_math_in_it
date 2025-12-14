#ifndef INVERSE_H
#define INVERSE_H

#include "matrix.h"
#include "determinant.h"

// Matrix inversion
int inverse_gauss_jordan(double** a, double** inv, int n);
int inverse_via_lu(double** a, double** inv, int n);

#endif // INVERSE_H