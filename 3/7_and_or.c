#include <stdio.h>

int f1() {
    printf("Wywolano f1\n");
    return 1;   //0
}

int f2() {
    printf("Wywolano f2\n");
    return 1;
}

int main(void) {
    if (f1() && f2()) printf("Spelniony\n");
    if (f1() || f2()) printf("Spelniony\n");
}