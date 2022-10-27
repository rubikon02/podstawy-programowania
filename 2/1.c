#include <stdio.h>

int main() {
    int a, b, c, x;
    x = (a = 5, b = 3, c = a + b);
    printf("%d", x); //8
}