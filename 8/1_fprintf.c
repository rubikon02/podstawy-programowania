#include <stdio.h>


int main() {
    FILE *file;
    file = fopen("plik1.txt", "w");
    if (!file) {
        printf("Blad otwarcia\n");
        return 0;
    }
    for (int i = 1; i <= 100; i++) {
        fprintf(file, "%d ", i);
    }
    fclose(file);
}