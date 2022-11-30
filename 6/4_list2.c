#include <stdio.h>
#include <stdlib.h>

struct student {
    int ocena;
    char nazwisko[10];
    struct student *nastepny;
};

void wczytaj(struct student *student) {
    printf("Podaj ocene:");
    scanf("%d", &student->ocena);
    printf("Podaj nazwisko:");
    scanf("%s", student->nazwisko);
}

void wypisz(struct student *student) {
    printf("Student %s z ocena %d\n", student->nazwisko, student->ocena);
}

void wypisz_liste(struct student *student) {
    while (student) {
        wypisz(student);
        student = student->nastepny;
    }
}

int main() {
    struct student *ws1, *ws2;
    ws1 = malloc(sizeof(struct student));
    wczytaj(ws1);
    ws2 = malloc(sizeof(struct student));
    wczytaj(ws2);
    ws1->nastepny = ws2;
    ws2->nastepny = 0;
    wypisz_liste(ws1);
    free(ws1);
    free(ws2);
}
