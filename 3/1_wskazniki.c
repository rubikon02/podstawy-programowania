#include <stdio.h>

int main(void) {
    int a, *ws, tab[] = {1, 3, 4, 5, 6, 1, 4, 6, 7, 2};
    ws = tab;
    printf("%d\n", *ws);
    printf("%p\n", ws);
    ws++;
    printf("%p\n", ws);
    ws = tab + 5;
    printf("%d\n", *ws);
    printf("%p\n", ws);

    ws = tab;
    a = *ws;
    printf("%d\n", a);
    a = *(ws + 4);
    printf("%d\n", a);
    a = *ws + 4;
    printf("%d\n", a);
    a = ws[4];
    printf("%d\n", a);
    a = ws[0] + 4;
    printf("%d\n", a);
    a = *(tab + 4);
    printf("%d\n", a);
}