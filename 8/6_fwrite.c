#include <stdio.h>

int main() {
    FILE *file = fopen("..\\8\\plik6.txt", "w");
    char ciag[] = "dane do zapisu";
    int w = fwrite((const void *)ciag, 1, 14, file);
    fclose(file);
    printf("Udalo sie zapisac %d blokow %d bajtowych\n", w, 1);
}