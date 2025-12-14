#include "utils.h"

int is_zero(double val) {
    return fabs(val) < EPS;
}

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int read_int(const char* prompt, int min, int max) {
    int val;
    int result;
    
    while (1) {
        printf("%s", prompt);
        result = scanf("%d", &val);
        
        if (result != 1) {
            printf("Error: please enter an integer.\n");
            clear_input_buffer();
            continue;
        }
        
        clear_input_buffer();
        
        if (val < min || val > max) {
            printf("Error: number must be between %d and %d.\n", min, max);
            continue;
        }
        
        return val;
    }
}

void pause_screen(void) {
    printf("\nPress Enter to continue...");
    getchar();
}