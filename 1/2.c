#include <stdio.h>

int main(void) {
    float a, b;     //double naprawia problem
    a = 1.0e10 + 1;
    b = a - 1.0e10;
    printf("%f\n", b);
}