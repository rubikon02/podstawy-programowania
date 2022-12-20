#include <stdio.h>

int main() {
    FILE *file = fopen("plik3.txt", "w");
    if (!file) {
        printf("Blad otwarcia\n");
        return 0;
    }
    for (char c = 'a'; c <= 'z'; c++) fputc(c, file);
    fclose(file);
}