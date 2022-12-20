#include <stdio.h>

int main() {
    FILE *file = fopen("plik6.txt", "w");
    if (!file) {
        printf("Blad otwarcia\n");
        return 0;
    }
    char ciag[] = "dane do zapisu";
    int w = fwrite((const void *) ciag, 1, 14, file);
    fclose(file);
    printf("Udalo sie zapisac %d blokow %d bajtowych\n", w, 1);
}