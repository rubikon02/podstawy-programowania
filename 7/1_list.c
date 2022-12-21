#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    int ocena;
    char nazwisko[100];
    struct student *nastepny;
};

struct student *nowy_el(char *nazwisko, int ocena) {
    struct student *nowy = malloc(sizeof(struct student));
    nowy->ocena = ocena;
    strcpy(nowy->nazwisko, nazwisko);
    nowy->nastepny = 0;
    return nowy;
}

struct student *wczytaj_el() {
    struct student *nowy = nowy_el("", 0);
    printf("Podaj ocene:");
    scanf("%d", &nowy->ocena);
    printf("Podaj nazwisko:");
    scanf("%s", nowy->nazwisko);
    return nowy;
}

void wypisz_el(struct student student) {
    printf("Student %s z ocena %d\n", student.nazwisko, student.ocena);
}

void wypisz_liste(struct student *student) {
    while (student) {
        wypisz_el(*student);
        student = student->nastepny;
    }
}

void dodaj_el(struct student **pierwszy, char *nazwisko, int ocena) {
    struct student *ww = *pierwszy;
    struct student *nowy = nowy_el(nazwisko, ocena);
    if (ww == 0) {
        *pierwszy = nowy;
    } else {
        while (ww->nastepny) ww = ww->nastepny;
        ww->nastepny = nowy;
    }
}

void zwolnij_liste(struct student **student) {
    if (!student) return;
    struct student *ww = *student;
    while (ww) {
        struct student *poprzedni = ww;
        ww = ww->nastepny;
//        printf("zwalniam %s\n", poprzedni->nazwisko);
        free(poprzedni);
    }
    *student = 0;
}

void wstaw_el(struct student **pierwszy, char *nazwisko, int ocena) {
    struct student *ww = *pierwszy;

    struct student *nowy = malloc(sizeof(struct student));
    nowy->ocena = ocena;
    strcpy(nowy->nazwisko, nazwisko);

    if (ww == 0 || nowy->ocena < ww->ocena) {
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

struct student *znajdz_element(struct student *ww, int ocena) {
    while (ww) {
        if (ww->ocena == ocena) return ww;
        ww = ww->nastepny;
    }
    return 0;
}

void usun_element(struct student **pierwszy, int ocena) {
    struct student *ww = *pierwszy, *poprzedni;
    if (ww == 0) return;
    if (ww->ocena == ocena) {
        *pierwszy = ww->nastepny;
        free(ww);
        return;
    }
    while (ww) {
        if (ww->ocena == ocena) {
            poprzedni->nastepny = ww->nastepny;
            free(ww);
            return;
        }
        poprzedni = ww;
        ww = ww->nastepny;
    }
}

int main() {
    struct student *ws = 0;

//    struct student *b = wczytaj_el();
//    dodaj_el(&ws, b->nazwisko, b->ocena);

    dodaj_el(&ws, "nazwisko1", 1);
    dodaj_el(&ws, "nazwisko2", 4);
    dodaj_el(&ws, "nazwisko3", 10);
    wstaw_el(&ws, "wstawiony", 3);
    wypisz_liste(ws);

    struct student *znaleziony = znajdz_element(ws, 1);
    if (znaleziony) {
        printf("Znalazlem %s z ocena %d\n", znaleziony->nazwisko, znaleziony->ocena);
    } else {
        printf("Nie znalazlem takiego studenta\n");
    }

    printf("Usuwam element\n");
    usun_element(&ws, 1);
    wypisz_liste(ws);

    zwolnij_liste(&ws);
}
