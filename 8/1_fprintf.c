#include <stdio.h>


int main() {
    FILE *wsk;
    wsk = fopen("..\\8\\plik1.txt", "w");
    if (!wsk) printf("Blad otwarcia\n");
//    int w = fprintf(wsk, "%d %lf\n", 5, 4.5);
    for (int i = 1; i <= 100; i++) {
        fprintf(wsk, "%d ", i);
    }
    fclose(wsk);
}