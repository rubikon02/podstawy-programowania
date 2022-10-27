#include <stdio.h>

int main(void) {
    int tab[4][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}}, (*tws)[3]; //wsk do tab 3-el
    printf("%p\n", tab);
    printf("%p\n", tab[0]);
    printf("%p\n", tab + 1);
    printf("%p\n", tab[0] + 1);
    tws = tab;
}