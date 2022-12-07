#include <stdio.h>
#include <stdint.h>
#include <string.h>

//todo zapisywanie do pliku i wypisywanie ich z pliku

struct blok {
    uint16_t hasz;
    uint16_t hasz_pop;
    uint16_t nonce;
    uint16_t nr_bloku;
    char zawartosc[100];
};

void wypelnij_blok(struct blok *blok, uint16_t nr_bloku, uint16_t hash_pop, char* zawartosc) {
    blok->nr_bloku = nr_bloku;
    blok->hasz_pop = hash_pop;
    strcpy(blok->zawartosc, zawartosc);
}

void kopanie(struct blok *blok) {
    uint16_t *ws = &blok->hasz_pop;
    for (int j = 0; j < 256*256; j++) {
        blok->nonce = j;
        int w = 0;
        for (int i = 0; i < 53; i++) {
            w += *ws;
            w = w % (256*256);
            w++;
//        blok->nonce = i;
//        blok->hasz = 0;
////        blok->hasz += blok->hasz_pop % 256 * 256;
////        blok->hasz += blok->nonce % 256 * 256;
////        blok->hasz += blok->nr_bloku % 256 * 256;
//        blok->hasz += blok->hasz_pop % 25;
//        blok->hasz += blok->nonce % 25;
//        blok->hasz += blok->nr_bloku % 25;
////        blok->hasz += (uint16_t) blok->zawartosc % 256 * 256;
//        if (blok->hasz == blok->nr_bloku * 10) return;
        }
        if (w == blok->nr_bloku * 10) {
            return;
        }
    }
}

void wypisz(struct blok *blok) {
    printf("Blok: %d\n", blok->nr_bloku);
    printf("\thasz: %d\n", blok->hasz);
    printf("\thasz_pop: %d\n", blok->hasz_pop);
    printf("\tnonce: %d\n", blok->nonce);
    printf("\tzawartosc: %s\n", blok->zawartosc);
}

int main() {
    struct blok b1, b2, b3;
//    uint16_t *ws;
//    ws = &(b1.hasz_pop);

    wypelnij_blok(&b1, 1, 0, "ala ma kota");
    kopanie(&b1);
    wypisz(&b1);

    wypelnij_blok(&b2, 1, b1.hasz, "tekst w bloku nr 2");
    kopanie(&b2);
    wypisz(&b2);

    wypelnij_blok(&b3, 1, b2.hasz, "a to zawartosc bloku 3");
    kopanie(&b3);
    wypisz(&b3);

//    zapisz_do_pliku(&b1);
//    zapisz_do_pliku(&b2);
//    zapisz_do_pliku(&b3);
//    wypisz_bloki_z_pliku();
}