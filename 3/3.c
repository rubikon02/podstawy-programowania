#include <stdio.h>

int main(void) {
    unsigned char *ws, a=1, b=2, c=3;
    ws = &b;
    ws++;
    *ws = 55;
    printf("%d\n", *ws);
    printf("%d\n", a);
    printf("%p\n", ws);
}