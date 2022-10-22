//koło o podanym rozmiarze z gwiazdek

#include <stdio.h>

int main(void) {
    int size;
    scanf("%d", &size);
    float r = size / 2.0f;
    for(float y = -r; y < size - r + 1; y++) {
        for(float x = -r; x < size - r + 1; x++) {
            if (x * x + y * y <= r * r) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}
