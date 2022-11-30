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
        printf("  ");
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
    if (w < ww->w) {
        while (ww->lewy) ww = ww->lewy;
        ww->lewy = nowy;
    } else {
        while (ww->prawy) ww = ww->prawy;
        ww->prawy = nowy;
    }
}

struct el_drzewa * znajdz(struct el_drzewa **pierwszy, int w) {
    struct el_drzewa *ww = *pierwszy;
    if (ww == 0) return 0;
    while (1) {
        if (w < ww->w) {
            ww = ww->lewy;
        } else if (w > ww->w) {
            ww = ww->prawy;
        } else {
            return ww;
        }
    }
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
    struct el_drzewa *ws;
    wstaw(&ws, 4);
    wstaw(&ws, 6);
    wstaw(&ws, 3);
    wypisz(&ws, 0);
    printf("%d\n", znajdz(&ws, 4)->w);
    zwolnij(&ws);
}
