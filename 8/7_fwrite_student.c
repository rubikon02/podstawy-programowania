#include <stdio.h>

struct student {
    int ocena;
    char nazwisko[10];
};

int main() {
    struct student s1 = {.ocena = 5, .nazwisko = "nazwisko"};
    struct student s2 = {.ocena = 5, .nazwisko = "nazwisko"};
    FILE *file = fopen("..\\8\\plik7.txt", "w");
    fwrite(&s1, sizeof(struct student), 1, file);
    fwrite(&s2, sizeof(struct student), 1, file);
    fclose(file);
}