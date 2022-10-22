//tabela

#include <stdio.h>

int main(void) {
    int size;
    scanf("%d", &size);

    for (int i = 0; i < size; i++) {
        printf(" %c", 'a' + i);
    }
    printf("\n");

    for (int y = 0; y < size; y++) {
        for (int i = 0; i < size * 2 + 1; i++) {
            printf("-");
        }
        printf("\n");
        for (int i = 0; i < size * 2 + 1; i++) {
            printf(i % 2 ? " " : "|");
        }
        printf(" %d\n", y + 1);
    }

    for (int i = 0; i < size * 2 + 1; i++) {
        printf("-");
    }
}
