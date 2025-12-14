#include "minors.h"

double minor_at(double** a, int n, int row, int col) {
    if (n == 1) return 1.0;
    
    double** submatrix = alloc_matrix(n - 1);
    
    int sub_i = 0;
    for (int i = 0; i < n; i++) {
        if (i == row) continue;
        int sub_j = 0;
        for (int j = 0; j < n; j++) {
            if (j == col) continue;
            submatrix[sub_i][sub_j] = a[i][j];
            sub_j++;
        }
        sub_i++;
    }
    
    double det;
    if (n - 1 <= 4) {
        det = det_recursive(submatrix, n - 1);
    } else {
        det = det_lu(submatrix, n - 1);
    }
    
    free_matrix(submatrix, n - 1);
    return det;
}

double cofactor_at(double** a, int n, int row, int col) {
    double minor_val = minor_at(a, n, row, col);
    int sign = ((row + col) % 2 == 0) ? 1 : -1;
    return sign * minor_val;
}

void cofactor_matrix(double** a, double** cof, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cof[i][j] = cofactor_at(a, n, i, j);
        }
    }
}