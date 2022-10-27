#include <stdio.h>

int main(void) {
    int a, *w1, **w2, ***w3, ****w4;
    a = 4; w1 = &a; w2 = &w1; w3 = &w2; w4 = &w3;
    printf("%d\n", ****w4);
    printf("%d\n", ***w3);
    printf("%d\n", **w2);
}