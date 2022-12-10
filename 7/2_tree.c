#include <stdio.h>
#include <stdlib.h>

struct el_drzewa {
    int w;
    struct el_drzewa *lewy, *prawy;
};

struct el_drzewa *nowy_el(int w, struct el_drzewa *lewy, struct el_drzewa *prawy) {
    struct el_drzewa *nowy = malloc(sizeof(struct el_drzewa));
    nowy->w = w;
    nowy->lewy = lewy;
    nowy->prawy = prawy;
    return nowy;
}

void wypisz(const struct el_drzewa *ww, int depth) {
    if (!ww) return;
    wypisz(ww->lewy, depth + 1);
    for (int i = 0; i < depth; i++) {
        printf(" ");
    }
    printf("%d: %d\n", depth, ww->w);
    wypisz(ww->prawy, depth + 1);
}

void wstaw(struct el_drzewa **pierwszy, int w) {
    struct el_drzewa *nowy = nowy_el(w, 0, 0);
    struct el_drzewa *ww = *pierwszy;

    if (ww == 0) {
        *pierwszy = nowy;
        return;
    }
    while (1) {
        if (w < ww->w) {
            if (ww->lewy) {
                ww = ww->lewy;
            } else {
                ww->lewy = nowy;
                return;
            }
        } else {
            if (ww->prawy) {
                ww = ww->prawy;
            } else {
                ww->prawy = nowy;
                return;
            }
        }
    }
}

struct el_drzewa *znajdz(struct el_drzewa **pierwszy, int w) {
    struct el_drzewa *ww = *pierwszy;
    while (1) {
        if (ww == 0) return 0;
        if (w < ww->w) {
            ww = ww->lewy;
        } else if (w > ww->w) {
            ww = ww->prawy;
        } else {
            return ww;
        }
    }
}

struct el_drzewa *skopiuj_drzewo(const struct el_drzewa *el_drzewa) {
    if (!el_drzewa) return 0;
    return nowy_el(
            el_drzewa->w,
            el_drzewa->lewy ? skopiuj_drzewo(el_drzewa->lewy) : 0,
            el_drzewa->prawy ? skopiuj_drzewo(el_drzewa->prawy) : 0
    );
}

struct el_drzewa *dodaj_drzewa_rekurencja(struct el_drzewa *a, const struct el_drzewa *b) {
    if (!a) return skopiuj_drzewo(b);
    if (!b) return skopiuj_drzewo(a);
    a->w += b->w;
    a->lewy = dodaj_drzewa_rekurencja(a->lewy, b->lewy);
    a->prawy = dodaj_drzewa_rekurencja(a->prawy, b->prawy);
    return a;
}

struct el_drzewa *dodaj_drzewa(const struct el_drzewa *a, const struct el_drzewa *b) {
    return dodaj_drzewa_rekurencja(skopiuj_drzewo(a), b);
}

void zwolnij(struct el_drzewa **pierwszy) {
    struct el_drzewa *ww = *pierwszy;
    if (!ww) return;
    zwolnij(&ww->lewy);
    zwolnij(&ww->prawy);
    printf("zwalniam %d\n", ww->w);
    free(ww);
    *pierwszy = 0;
}

int main() {
    struct el_drzewa *ws = 0;
    wstaw(&ws, 5);
    wstaw(&ws, 6);
    wstaw(&ws, 7);
    wstaw(&ws, 10);
    wstaw(&ws, 9);
    wstaw(&ws, 12);
    wstaw(&ws, 1);
    wstaw(&ws, 3);
    wstaw(&ws, 2);
    wstaw(&ws, 0);
    wypisz(ws, 0);

    struct el_drzewa *znaleziony = znajdz(&ws, 3);
    if (znaleziony) {
        printf("Znalazlem %d\n", znaleziony->w);
    } else {
        printf("Nie ma takiego elementu\n");
    }

//    struct el_drzewa *kopia = skopiuj_drzewo(ws);
//    zwolnij(&ws);
//    printf("Kopia drzewa:\n");
//    wypisz(&kopia, 0);

    wypisz(dodaj_drzewa(ws, ws), 0);
}
