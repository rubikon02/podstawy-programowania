//tabela z całą kolumną i wierszem x

#include <stdio.h>

int main(void) {
    printf("Podaj rozmiar: ");
    int size;
    scanf("%d", &size);
    printf("Podaj litere kolumny: ");
    char letter;
    scanf("\n%c", &letter);
    printf("Podaj linie: ");
    int row;
    scanf("%d", &row);

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
            if (i % 2) {
                if (y == row - 1 || (i % 2 == 1 && (i - 1) / 2 == letter - 'a')) {
                    printf("x");
                } else {
                    printf(" ");
                }
            } else {
                printf("|");
            }
        }
        printf(" %d\n", y + 1);
    }

    for (int i = 0; i < size * 2 + 1; i++) {
        printf("-");
    }
}
