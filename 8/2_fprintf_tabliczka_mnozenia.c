#include <stdio.h>

int main() {
    FILE *wsk;
    wsk = fopen("..\\8\\plik2.txt", "w");
    if (!wsk) printf("Blad otwarcia\n");
//    int w = fprintf(wsk, "%d %lf\n", 5, 4.5);
    fprintf(wsk, "x\t");
    for (int x = 1; x <= 10; x++) {
        fprintf(wsk, "%d\t", x);
    }
    fprintf(wsk, "\n");
    for (int x = 1; x <= 10; x++) {
        fprintf(wsk, "%d\t", x);

        for (int y = 1; y <= 10; y++) {
            fprintf(wsk, "%d\t", x * y);
        }
        fprintf(wsk, "\n");
    }
    fclose(wsk);
}