//choinka z trzema poziomami o podanym rozmiarze z gwiazdek

#include <stdio.h>

int main(void) {
    int size;
    scanf("%d", &size);
    for (int i = 2; i >= 0; i--) {
        for (int y = 0; y < size - i; y++) {
            for (int x = 0; x < size + y; x++) {
                printf(x >= size - y - 1 ? "*" : " ");
            }
            printf("\n");
        }
    }
}
