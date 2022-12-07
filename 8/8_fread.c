#include <stdio.h>

struct student {
    int ocena;
    char nazwisko[10];
};

int main() {
    struct student s1;
    FILE *file = fopen("..\\8\\plik7.txt", "r");
    while (1) {
        fread(&s1, sizeof(struct student), 1, file);
        if (feof(file)) break;
        printf("%d %s\n", s1.ocena, s1.nazwisko);
    }
    fclose(file);
}