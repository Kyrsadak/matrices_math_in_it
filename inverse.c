#include "inverse.h"

int inverse_gauss_jordan(double** a, double** inv, int n) {
    // Create augmented matrix [A | I]
    double** aug = alloc_matrix(n);
    for (int i = 0; i < n; i++) {
        aug[i] = (double*)realloc(aug[i], 2 * n * sizeof(double));
        if (!aug[i]) {
            fprintf(stderr, "Error: memory allocation failed.\n");
            free_matrix(aug, n);
            return 0;
        }
    }
    
    // Initialize augmented matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            aug[i][j] = a[i][j];
            aug[i][j + n] = (i == j) ? 1.0 : 0.0;
        }
    }
    
    // Gauss-Jordan elimination with partial pivoting
    for (int k = 0; k < n; k++) {
        // Find pivot
        int pivot_row = k;
        double max_val = fabs(aug[k][k]);
        
        for (int i = k + 1; i < n; i++) {
            if (fabs(aug[i][k]) > max_val) {
                max_val = fabs(aug[i][k]);
                pivot_row = i;
            }
        }
        
        // Check singularity
        if (is_zero(max_val)) {
            free_matrix(aug, n);
            return 0;
        }
        
        // Swap rows
        if (pivot_row != k) {
            double* temp = aug[k];
            aug[k] = aug[pivot_row];
            aug[pivot_row] = temp;
        }
        
        // Normalize pivot row
        double pivot = aug[k][k];
        for (int j = 0; j < 2 * n; j++) {
            aug[k][j] /= pivot;
        }
        
        // Eliminate column
        for (int i = 0; i < n; i++) {
            if (i == k) continue;
            double factor = aug[i][k];
            for (int j = 0; j < 2 * n; j++) {
                aug[i][j] -= factor * aug[k][j];
            }
        }
    }
    
    // Extract inverse from right half
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inv[i][j] = aug[i][j + n];
        }
    }
    
    free_matrix(aug, n);
    return 1;
}

int inverse_via_lu(double** a, double** inv, int n) {
    double** lu = alloc_matrix(n);
    copy_matrix(a, lu, n);
    
    int* perm = (int*)malloc(n * sizeof(int));
    int sign;
    
    if (!lu_decompose(lu, n, perm, &sign)) {
        free_matrix(lu, n);
        free(perm);
        return 0;
    }
    
    // Solve for each column of identity matrix
    double* b = (double*)malloc(n * sizeof(double));
    double* x = (double*)malloc(n * sizeof(double));
    
    for (int col = 0; col < n; col++) {
        // Set up unit vector
        for (int i = 0; i < n; i++) {
            b[i] = (i == col) ? 1.0 : 0.0;
        }
        
        // Apply permutation to b
        double* pb = (double*)malloc(n * sizeof(double));
        for (int i = 0; i < n; i++) {
            pb[i] = b[perm[i]];
        }
        
        // Forward substitution (Ly = Pb)
        for (int i = 0; i < n; i++) {
            x[i] = pb[i];
            for (int j = 0; j < i; j++) {
                x[i] -= lu[i][j] * x[j];
            }
        }
        
        // Backward substitution (Ux = y)
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i + 1; j < n; j++) {
                x[i] -= lu[i][j] * x[j];
            }
            x[i] /= lu[i][i];
        }
        
        // Copy solution to inv column
        for (int i = 0; i < n; i++) {
            inv[i][col] = x[i];
        }
        
        free(pb);
    }
    
    free(b);
    free(x);
    free_matrix(lu, n);
    free(perm);
    
    return 1;
}