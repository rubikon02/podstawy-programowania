#include <stdio.h>

int main() {
    FILE *file = fopen("..\\8\\plik3.txt", "w");
    for (char c = 'a'; c <= 'z'; c++) fputc(c, file);
    fclose(file);
}