#include "determinant.h"

double det_2x2(double** m) {
    return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

double det_sarrus_3x3(double** m) {
    return m[0][0] * m[1][1] * m[2][2] +
           m[0][1] * m[1][2] * m[2][0] +
           m[0][2] * m[1][0] * m[2][1] -
           m[0][2] * m[1][1] * m[2][0] -
           m[0][0] * m[1][2] * m[2][1] -
           m[0][1] * m[1][0] * m[2][2];
}

double det_recursive(double** m, int n) {
    if (n == 1) return m[0][0];
    if (n == 2) return det_2x2(m);
    if (n == 3) return det_sarrus_3x3(m);
    
    double det = 0.0;
    double** submatrix = alloc_matrix(n - 1);
    
    for (int col = 0; col < n; col++) {
        // Build submatrix
        int sub_i = 0;
        for (int i = 1; i < n; i++) {
            int sub_j = 0;
            for (int j = 0; j < n; j++) {
                if (j == col) continue;
                submatrix[sub_i][sub_j] = m[i][j];
                sub_j++;
            }
            sub_i++;
        }
        
        double sign = (col % 2 == 0) ? 1.0 : -1.0;
        det += sign * m[0][col] * det_recursive(submatrix, n - 1);
    }
    
    free_matrix(submatrix, n - 1);
    return det;
}

int lu_decompose(double** a, int n, int* perm, int* sign) {
    *sign = 1;
    
    // Initialize permutation
    for (int i = 0; i < n; i++) {
        perm[i] = i;
    }
    
    for (int k = 0; k < n; k++) {
        // Find pivot
        int pivot_row = k;
        double max_val = fabs(a[k][k]);
        
        for (int i = k + 1; i < n; i++) {
            if (fabs(a[i][k]) > max_val) {
                max_val = fabs(a[i][k]);
                pivot_row = i;
            }
        }
        
        // Check for singularity
        if (is_zero(max_val)) {
            return 0; // Matrix is singular
        }
        
        // Swap rows if needed
        if (pivot_row != k) {
            swap_rows(a, n, k, pivot_row);
            int temp = perm[k];
            perm[k] = perm[pivot_row];
            perm[pivot_row] = temp;
            *sign *= -1;
        }
        
        // Eliminate below
        for (int i = k + 1; i < n; i++) {
            a[i][k] /= a[k][k];
            for (int j = k + 1; j < n; j++) {
                a[i][j] -= a[i][k] * a[k][j];
            }
        }
    }
    
    return 1; // Success
}

double det_lu(double** m, int n) {
    double** a = alloc_matrix(n);
    copy_matrix(m, a, n);
    
    int* perm = (int*)malloc(n * sizeof(int));
    int sign;
    
    if (!lu_decompose(a, n, perm, &sign)) {
        free_matrix(a, n);
        free(perm);
        return 0.0; // Singular matrix
    }
    
    // Product of diagonal elements
    double det = (double)sign;
    for (int i = 0; i < n; i++) {
        det *= a[i][i];
    }
    
    free_matrix(a, n);
    free(perm);
    
    return det;
}