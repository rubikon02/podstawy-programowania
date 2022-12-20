#include <stdio.h>

int main() {
    FILE *file = fopen("plik2.txt", "r");
    if (!file) {
        printf("Blad otwarcia\n");
        return 0;
    }
    int w;
    while ((w = fgetc(file)) != EOF) printf("%c", w);
    fclose(file);
}