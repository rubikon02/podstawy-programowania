#include <stdio.h>

int main() {
    FILE *file = fopen("plik2.txt", "r");
    if (!file) {
        printf("Blad otwarcia\n");
        return 0;
    }
    int value;
    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 11; x++) {
            if (x == 0 && y == 0) {
                fscanf(file, "\t");
                printf("\t");
            } else {
                fscanf(file, "%d\t", &value);
                printf("%d\t", value);
            }
        }
        printf("\n");
    }
    fclose(file);
}