#include <stdio.h>

int main() {
    FILE *file = fopen("..\\8\\plik2.txt", "r");
    int w;
    while ((w = fgetc(file)) != EOF) printf("%c", w);
    fclose(file);
}