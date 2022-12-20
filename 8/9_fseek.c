#include <stdio.h>

struct student {
    int ocena;
    char nazwisko[10];
};

int main() {
    int student_i = 1;
    struct student s1;
    FILE *file = fopen("plik7.txt", "r");
    if (!file) {
        printf("Blad otwarcia\n");
        return 0;
    }
    fseek(file, student_i * sizeof(struct student), SEEK_SET);
    fread(&s1, sizeof(struct student), 1, file);
    printf("%d %s\n", s1.ocena, s1.nazwisko);
    fclose(file);
}