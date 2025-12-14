#include "matrix.h"

double** alloc_matrix(int n) {
    double** m = (double**)malloc(n * sizeof(double*));
    if (!m) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        exit(1);
    }
    
    for (int i = 0; i < n; i++) {
        m[i] = (double*)malloc(n * sizeof(double));
        if (!m[i]) {
            fprintf(stderr, "Error: memory allocation failed.\n");
            for (int j = 0; j < i; j++) free(m[j]);
            free(m);
            exit(1);
        }
    }
    return m;
}

void free_matrix(double** m, int n) {
    if (!m) return;
    for (int i = 0; i < n; i++) {
        if (m[i]) free(m[i]);
    }
    free(m);
}

void read_matrix(double** m, int n) {
    printf("Enter matrix elements (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++) {
        printf("Row %d: ", i + 1);
        for (int j = 0; j < n; j++) {
            if (scanf("%lf", &m[i][j]) != 1) {
                fprintf(stderr, "Error: invalid input.\n");
                clear_input_buffer();
                j--;
            }
        }
    }
    clear_input_buffer();
}

void read_matrix_from_file(double** m, int n, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "Error: cannot open file '%s'.\n", filename);
        return;
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fscanf(f, "%lf", &m[i][j]) != 1) {
                fprintf(stderr, "Error: invalid format in file.\n");
                fclose(f);
                return;
            }
        }
    }
    fclose(f);
    printf("Matrix loaded from '%s'.\n", filename);
}

void print_matrix(double** m, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Remove trailing zeros for cleaner output
            if (fabs(m[i][j]) < EPS) {
                printf("%10.2f ", 0.0);
            } else if (fabs(m[i][j] - (int)m[i][j]) < EPS) {
                printf("%10.0f ", m[i][j]);
            } else {
                printf("%10.4f ", m[i][j]);
            }
        }
        printf("\n");
    }
}

void save_matrix_to_file(double** m, int n, const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        fprintf(stderr, "Error: cannot write to file '%s'.\n", filename);
        return;
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(f, "%.10f ", m[i][j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
    printf("Matrix saved to '%s'.\n", filename);
}

void copy_matrix(double** src, double** dst, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dst[i][j] = src[i][j];
        }
    }
}

void identity_matrix(double** m, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            m[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }
}

void swap_rows(double** m, int n, int row1, int row2) {
    if (row1 == row2) return;
    double* temp = m[row1];
    m[row1] = m[row2];
    m[row2] = temp;
}