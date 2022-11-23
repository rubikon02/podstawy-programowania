#include <stdio.h>

struct student {
    int ocena;
    char nazwisko[10];
};

void wczytaj(struct student *student) {
    printf("Podaj ocene:");
    scanf("%d", &student->ocena);
    printf("Podaj nazwisko:");
    scanf("%s", student->nazwisko);
}

void wypisz(struct student student) {
    printf("Student %s z ocena %d\n", student.nazwisko, student.ocena);
}

int main() {
    struct student s1, s2;
    wczytaj(&s1);
    wczytaj(&s2);
    wypisz(s1);
    wypisz(s2);
}
