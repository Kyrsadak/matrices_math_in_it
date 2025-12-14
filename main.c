#include "matrix.h"
#include "determinant.h"
#include "minors.h"
#include "inverse.h"

void print_menu(void) {
    printf("\n=== MATRIX CALCULATOR ===\n");
    printf("1. Calculate Determinant\n");
    printf("2. Calculate Minor\n");
    printf("3. Calculate Cofactor\n");
    printf("4. Calculate Cofactor Matrix\n");
    printf("5. Calculate Inverse Matrix\n");
    printf("6. Display Matrix\n");
    printf("7. Enter New Matrix\n");
    printf("8. Load Matrix from File\n");
    printf("9. Save Matrix to File\n");
    printf("0. Exit\n");
    printf("========================\n");
}

int main(void) {
    int n = 0;
    double** matrix = NULL;
    int choice;
    
    printf("MODULAR MATRIX CALCULATOR\n");
    printf("Supports 2x2, 3x3, 4x4, and NxN matrices (N <= %d)\n\n", MAX_N);
    
    // Initial matrix input
    n = read_int("Enter matrix size (2-%d): ", 2, MAX_N);
    matrix = alloc_matrix(n);
    read_matrix(matrix, n);
    
    while (1) {
        print_menu();
        choice = read_int("Enter your choice: ", 0, 9);
        
        switch (choice) {
            case 1: { // Determinant
                double det;
                if (n == 2) {
                    det = det_2x2(matrix);
                    printf("\nDeterminant (2x2 formula): %.10f\n", det);
                } else if (n == 3) {
                    det = det_sarrus_3x3(matrix);
                    printf("\nDeterminant (Sarrus rule): %.10f\n", det);
                } else if (n <= 4) {
                    det = det_recursive(matrix, n);
                    printf("\nDeterminant (recursive): %.10f\n", det);
                } else {
                    det = det_lu(matrix, n);
                    printf("\nDeterminant (LU decomposition): %.10f\n", det);
                }
                
                if (is_zero(det)) {
                    printf("Note: Matrix is singular (|det| < %.0e)\n", EPS);
                }
                pause_screen();
                break;
            }
            
            case 2: { // Minor
                int row = read_int("Enter row index (1-%d): ", 1, n) - 1;
                int col = read_int("Enter column index (1-%d): ", 1, n) - 1;
                double minor = minor_at(matrix, n, row, col);
                printf("\nMinor M[%d][%d] = %.10f\n", row + 1, col + 1, minor);
                pause_screen();
                break;
            }
            
            case 3: { // Cofactor
                int row = read_int("Enter row index (1-%d): ", 1, n) - 1;
                int col = read_int("Enter column index (1-%d): ", 1, n) - 1;
                double cofactor = cofactor_at(matrix, n, row, col);
                printf("\nCofactor C[%d][%d] = %.10f\n", row + 1, col + 1, cofactor);
                pause_screen();
                break;
            }
            
            case 4: { // Cofactor matrix
                printf("\nCalculating cofactor matrix...\n");
                double** cof = alloc_matrix(n);
                cofactor_matrix(matrix, cof, n);
                printf("\nCofactor Matrix:\n");
                print_matrix(cof, n);
                free_matrix(cof, n);
                pause_screen();
                break;
            }
            
            case 5: { // Inverse
                double det = det_lu(matrix, n);
                if (is_zero(det)) {
                    printf("\nError: Matrix is singular (det = %.10f)\n", det);
                    printf("Cannot compute inverse.\n");
                } else {
                    printf("\nChoose inversion method:\n");
                    printf("1. Gauss-Jordan\n");
                    printf("2. LU Decomposition\n");
                    int method = read_int("Method: ", 1, 2);
                    
                    double** inv = alloc_matrix(n);
                    int success;
                    
                    if (method == 1) {
                        success = inverse_gauss_jordan(matrix, inv, n);
                    } else {
                        success = inverse_via_lu(matrix, inv, n);
                    }
                    
                    if (success) {
                        printf("\nInverse Matrix:\n");
                        print_matrix(inv, n);
                        
                        // Verify: A * A^-1 should be I
                        printf("\nVerification (A * A^-1):\n");
                        double** product = alloc_matrix(n);
                        for (int i = 0; i < n; i++) {
                            for (int j = 0; j < n; j++) {
                                product[i][j] = 0;
                                for (int k = 0; k < n; k++) {
                                    product[i][j] += matrix[i][k] * inv[k][j];
                                }
                            }
                        }
                        print_matrix(product, n);
                        free_matrix(product, n);
                    } else {
                        printf("\nError: Failed to compute inverse.\n");
                    }
                    
                    free_matrix(inv, n);
                }
                pause_screen();
                break;
            }
            
            case 6: { // Display matrix
                printf("\nCurrent Matrix (%dx%d):\n", n, n);
                print_matrix(matrix, n);
                pause_screen();
                break;
            }
            
            case 7: { // New matrix
                free_matrix(matrix, n);
                n = read_int("Enter new matrix size (2-%d): ", 2, MAX_N);
                matrix = alloc_matrix(n);
                read_matrix(matrix, n);
                break;
            }
            
            case 8: { // Load from file
                char filename[256];
                printf("Enter filename: ");
                if (scanf("%255s", filename) == 1) {
                    clear_input_buffer();
                    free_matrix(matrix, n);
                    n = read_int("Enter matrix size in file: ", 2, MAX_N);
                    matrix = alloc_matrix(n);
                    read_matrix_from_file(matrix, n, filename);
                }
                pause_screen();
                break;
            }
            
            case 9: { // Save to file
                char filename[256];
                printf("Enter filename: ");
                if (scanf("%255s", filename) == 1) {
                    clear_input_buffer();
                    save_matrix_to_file(matrix, n, filename);
                }
                pause_screen();
                break;
            }
            
            case 0: { // Exit
                printf("\nExiting program. Goodbye!\n");
                free_matrix(matrix, n);
                return 0;
            }
            
            default:
                printf("Invalid choice.\n");
                pause_screen();
        }
    }
    
    return 0;
}