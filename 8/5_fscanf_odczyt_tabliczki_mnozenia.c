#include <stdio.h>

int main() {
    FILE *file = fopen("..\\8\\plik2.txt", "r");
    int value;
    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 11; x++) {
            fscanf(file, "%d\t", &value);
            printf("%d\t", value);
        }
        printf("\n");
    }
//    while (fscanf(file, "%d\t", &value) != EOF) printf("%d ", value);
    fclose(file);
}