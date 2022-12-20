#include <stdio.h>

struct student {
    int ocena;
    char nazwisko[10];
};

int main() {
    struct student student;
    FILE *file = fopen("plik7.txt", "r");
    if (!file) {
        printf("Blad otwarcia\n");
        return 0;
    }
    while (1) {
        fread(&student, sizeof(struct student), 1, file);
        if (feof(file)) break;
        printf("%d %s\n", student.ocena, student.nazwisko);
    }
    fclose(file);
}