#include <stdio.h>

int main() {
    FILE *file;
    file = fopen("plik2.txt", "w");
    if (!file) {
        printf("Blad otwarcia\n");
        return 0;
    }
    fprintf(file, "\t");
    for (int x = 1; x <= 10; x++) {
        fprintf(file, "%d\t", x);
    }
    fprintf(file, "\n");
    for (int x = 1; x <= 10; x++) {
        fprintf(file, "%d\t", x);

        for (int y = 1; y <= 10; y++) {
            fprintf(file, "%d\t", x * y);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}