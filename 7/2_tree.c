#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct el_drzewa {
    int w;
    struct el_drzewa *lewy, *prawy;
};

void wypisz(struct el_drzewa **pierwszy, int depth) {
    struct el_drzewa *ww = *pierwszy;
    if (!ww) return;
    wypisz(&ww->lewy, depth + 1);
    for (int i = 0; i < depth; i++) {
        printf(" ");
    }
    printf("%d: %d\n", depth, ww->w);
    wypisz(&ww->prawy, depth + 1);
//    if (depth == 0) printf("      ");
//    printf("%d: %d\n", depth, ww->w);
//    if (ww->lewy) printf("lewy  ");
//    wypisz(&ww->lewy, depth + 1);
//    if (ww->prawy) printf("prawy ");
//    wypisz(&ww->prawy, depth + 1);
}

void wstaw(struct el_drzewa **pierwszy, int w) {
    struct el_drzewa *nowy = malloc(sizeof(struct el_drzewa)), *ww = *pierwszy;
    nowy->w = w;
    nowy->lewy = 0;
    nowy->prawy = 0;

    if (ww == 0) {
        *pierwszy = nowy;
        return;
    }
//    if (w < ww->w) {
//        while (ww->lewy) ww = ww->lewy;
//        ww->lewy = nowy;
//    } else {
//        while (ww->prawy) ww = ww->prawy;
//        ww->prawy = nowy;
//    }
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

struct el_drzewa * znajdz(struct el_drzewa **pierwszy, int w) {
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

struct el_drzewa * skopiuj_drzewo(struct el_drzewa *el_drzewa) {
    struct el_drzewa *nowy = malloc(sizeof(struct el_drzewa));
    nowy->w = el_drzewa->w;
    nowy->lewy = el_drzewa->lewy ? el_drzewa->lewy : 0;
    nowy->prawy = el_drzewa->prawy ? el_drzewa->prawy : 0;
    if (el_drzewa->lewy) skopiuj_drzewo(el_drzewa->lewy);
    if (el_drzewa->prawy) skopiuj_drzewo(el_drzewa->prawy);
    return nowy;
}

void zwolnij(struct el_drzewa **pierwszy) {
    struct el_drzewa *ww = *pierwszy;
    if (!ww) return;
    zwolnij(&ww->lewy);
    zwolnij(&ww->prawy);
    printf("zwalniam %d\n", ww->w);
    free(ww);
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
    wypisz(&ws, 0);

    struct el_drzewa *kopia = skopiuj_drzewo(ws);
    printf("Kopia drzewa:\n");
    wypisz(&kopia, 0);

    printf("%d\n", znajdz(&ws, 3)->w);
    zwolnij(&ws);
}
