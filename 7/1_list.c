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

void wstaw_el(struct student **pierwszy, int ocena) {
    struct student *ww = *pierwszy;

    struct student *nowy = malloc(sizeof(struct student));
    nowy->ocena = ocena;
    strcpy(nowy->nazwisko, "nazwisko_");

    if (ww == 0 || nowy->ocena < ww->nastepny->ocena) {
        nowy->nastepny = *pierwszy;
        *pierwszy = nowy;
    } else {
        while (ww->nastepny && nowy->ocena > ww->nastepny->ocena) {
            ww = ww->nastepny;
        }
        nowy->nastepny = ww->nastepny;
        ww->nastepny = nowy;
    }
}

struct student * znajdz_element(struct student **pierwszy, int ocena) {
    struct student *ww = *pierwszy;
    if (ww == 0) return 0;
    while (ww->nastepny && ww->ocena != ocena) {
        ww = ww->nastepny;
    }
    return ww;
}

void usun_element(struct student **pierwszy, int ocena) {
    struct student *ww = *pierwszy, *poprzedni;
    if (ww == 0) return;
    if (ww->ocena == ocena) {
        *pierwszy = ww->nastepny;
        free(ww);
        return;
    }
    poprzedni = ww;
    while (ww->nastepny && ww->ocena != ocena) {
        poprzedni = ww;
        ww = ww->nastepny;
    }
    poprzedni->nastepny = ww->nastepny;
    free(ww);
}

int main() {
    struct student *ws = 0;
    dodaj_el(&ws, "nazwisko1", 1);
    dodaj_el(&ws, "nazwisko2", 2);
    dodaj_el(&ws, "nazwisko3", 5);
    wstaw_el(&ws, 100);
    struct student *znaleziony = znajdz_element(&ws, 1);
    printf("%s\n", znaleziony->nazwisko);
    wypisz_liste(ws);
    usun_element(&ws, 100);
    wypisz_liste(ws);
    zwolnij_liste(ws);
}
