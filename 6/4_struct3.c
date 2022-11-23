#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    int ocena;
    char nazwisko[10];
    struct student *nastepny;
};

void wypisz(struct student student) {
    printf("Student %s z ocena %d\n", student.nazwisko, student.ocena);
}

void wypisz_liste(struct student *student) {
    while (student) {
        wypisz(*student);
        student = student->nastepny;
    }
}

void dodaj_el(struct student **pierwszy, char nazwisko[10], int ocena) {
    struct student *ww = *pierwszy;

    struct student *nowy_student = malloc(sizeof(struct student));
    nowy_student->ocena = ocena;
    nowy_student->nastepny = 0;
    strcpy(nowy_student->nazwisko, nazwisko);

    if (ww == 0) {
        *pierwszy = nowy_student;
    } else {
        while (ww->nastepny) ww = ww->nastepny;
        ww->nastepny = nowy_student;
    }
}

void zwolnij_liste(struct student *student) {
    do {
        struct student *temp = student;
        student = student->nastepny;
//        printf("zwalniam %s\n", temp->nazwisko);
        free(temp);
    } while (student);
}

int main() {
    struct student *ws = 0;
    dodaj_el(&ws, "nazwisko1", 5);
    dodaj_el(&ws, "nazwisko2", 5);
    dodaj_el(&ws, "nazwisko3", 5);
    wypisz_liste(ws);
    zwolnij_liste(ws);
}
