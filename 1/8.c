//kwadrat o podanym rozmiarze z gwiazdek

#include <stdio.h>

int main(void) {
    int count;
    scanf("%d", &count);
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            printf("*");
        }
        printf("\n");
    }
}