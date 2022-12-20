#include <stdio.h>

struct student {
    int ocena;
    char nazwisko[10];
};

int main() {
    struct student s1 = {.ocena = 5, .nazwisko = "nazwisko1"};
    struct student s2 = {.ocena = 4, .nazwisko = "nazwisko2"};
    FILE *file = fopen("plik7.txt", "w");
    if (!file) {
        printf("Blad otwarcia\n");
        return 0;
    }
    fwrite(&s1, sizeof(struct student), 1, file);
    fwrite(&s2, sizeof(struct student), 1, file);
    fclose(file);
}