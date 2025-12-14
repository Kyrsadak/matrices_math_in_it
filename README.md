# Modular Matrix Calculator

A comprehensive C-based matrix calculator with support for determinants, minors, cofactors, and matrix inversion.

## Features

- **Matrix Operations**:
  - Determinant calculation (Sarrus rule for 3×3, LU decomposition for general N×N)
  - Minor and cofactor computation
  - Cofactor matrix generation
  - Matrix inversion (Gauss-Jordan and LU methods)

- **Multiple Algorithms**:
  - Direct formulas for 2×2 and 3×3 matrices
  - Recursive expansion for small matrices (≤4×4)
  - LU decomposition with partial pivoting for larger matrices
  - Numerically stable implementations

- **Input/Output**:
  - Interactive console input
  - File I/O support
  - Matrix display with formatting
  - Input validation and error handling

- **Size Support**: 2×2, 3×3, 4×4, and general N×N (N ≤ 50)

## File Structure

```
matrix_calc/
├── main.c           # Main program with interactive menu
├── matrix.c/h       # Matrix allocation, I/O operations
├── determinant.c/h  # Determinant algorithms (Sarrus, LU, recursive)
├── minors.c/h       # Minor and cofactor calculations
├── inverse.c/h      # Matrix inversion algorithms
├── utils.c/h        # Utility functions and constants
├── Makefile         # Build configuration
└── README.md        # This file
```

## Compilation

### Using Make:
```bash
make
```

### Manual compilation:
```bash
gcc -Wall -Wextra -std=c99 -O2 main.c matrix.c determinant.c minors.c inverse.c utils.c -o matrix_calc -lm
```

## Usage

### Run the program:
```bash
./matrix_calc
```

### Interactive Menu:
1. **Calculate Determinant** - Compute det(A) using appropriate method
2. **Calculate Minor** - Compute minor M[i,j]
3. **Calculate Cofactor** - Compute cofactor C[i,j]
4. **Calculate Cofactor Matrix** - Generate complete cofactor matrix
5. **Calculate Inverse Matrix** - Find A⁻¹ (if it exists)
6. **Display Matrix** - Show current matrix
7. **Enter New Matrix** - Input a different matrix
8. **Load Matrix from File** - Read matrix from text file
9. **Save Matrix to File** - Write matrix to text file
0. **Exit** - Close program

## File Format

Matrix files should contain space-separated numbers:
```
1.0 2.0 3.0
4.0 5.0 6.0
7.0 8.0 9.0
```

## Examples

### Example 1: 3×3 Determinant (Sarrus Rule)
```
Input matrix:
1  2  3
0  1  4
5  6  0

Determinant = 1
```

### Example 2: Matrix Inversion
```
Input matrix:
4  7
2  6

Determinant = 10
Inverse Matrix:
 0.600000  -0.700000
-0.200000   0.400000

Verification (A * A⁻¹):
 1.000000   0.000000
 0.000000   1.000000
```

### Example 3: Minor and Cofactor
```
Matrix:
1  2  3
4  5  6
7  8  9

Minor M[2,2] = -3.000000
Cofactor C[2,2] = -3.000000
```

## Algorithms

### Determinant Methods:
- **2×2**: Direct formula `ad - bc`
- **3×3**: Sarrus rule (sum of diagonal products)
- **4×4**: Recursive cofactor expansion
- **N×N**: LU decomposition with partial pivoting

### Matrix Inversion:
- **Gauss-Jordan**: Row reduction with augmented matrix [A|I]
- **LU Decomposition**: Solve Ax = eᵢ for each column

### Numerical Stability:
- Partial pivoting (row swaps)
- Epsilon threshold (ε = 10⁻¹²) for singularity detection
- Double precision floating-point arithmetic

## Configuration

Edit `utils.h` to modify:
- `EPS` - Epsilon for zero comparisons (default: 1e-12)
- `MAX_N` - Maximum matrix size (default: 50)

## Error Handling

The program validates:
- Matrix dimensions (2 ≤ N ≤ MAX_N)
- Numeric input format
- File accessibility
- Matrix singularity (|det| < ε)

## Testing

Test with:
- Identity matrices (det = 1, A⁻¹ = A)
- Diagonal matrices
- Singular matrices (det = 0)
- Known examples with verified results

## Limitations

- Maximum size: 50×50 (configurable)
- Square matrices only
- Real numbers only (no complex support)
- Memory constraints for very large matrices

## Future Enhancements

- Complex number support
- Command-line arguments for batch processing
- LaTeX output format
- Additional decompositions (QR, SVD)
- Arbitrary precision arithmetic
- Matrix rank and null space calculation

## License

Educational project - free to use and modify.

## Author

Created by ~Turgunbayev Daulet~ in Inha University in Tashkent and School 21
