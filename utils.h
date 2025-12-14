#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1e-12
#define MAX_N 50

// Utility functions
int is_zero(double val);
void clear_input_buffer(void);
int read_int(const char* prompt, int min, int max);
void pause_screen(void);

#endif // UTILS_H