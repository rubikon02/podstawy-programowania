#include <stdio.h>

int main(void) {
    int tab[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, *wsk[10];
    for (int i = 0; i < 10; i++) {
        wsk[i] = &tab[9 - i];
    }
    for (int i = 0; i < 10; i++) {
        printf("%d\n", *wsk[i]);
    }
    for (int i = 0; i < 10; i++) {
        printf("%p\n", wsk[i]);
    }
}