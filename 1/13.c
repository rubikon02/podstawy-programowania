//bałwan o podanym rozmiarze z gwiazdek

#include <stdio.h>

void circle(int size, int shift) {
    float r = (size - shift * 2) / 2.0f;
    for(float y = -r; y < size - shift * 2 - r + 1; y++) {
        for (int i = 0; i < shift; i++) {
            printf(" ");
        }
        for(float x = -r; x < size - shift * 2 - r + 1; x++) {
            if (x * x + y * y <= r * r) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int main(void) {
    int size;
    scanf("%d", &size);
    circle(size, 2);
    circle(size, 1);
    circle(size, 0);
}
