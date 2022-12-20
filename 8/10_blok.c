#include <stdio.h>
#include <stdint.h>
#include <string.h>

struct blok {
    uint16_t hasz;
    uint16_t hasz_pop;
    uint16_t nonce;
    uint16_t nr_bloku;
    char zawartosc[100];
};

#define ILOSC_BLOKOW 3
#define NAZWA_PLIKU "bloki.txt"

void wypelnij_blok(struct blok *blok, uint16_t nr_bloku, uint16_t hash_pop, char *zawartosc);

void kopanie(struct blok *blok);

void wypisz(struct blok *blok);

void wypisz_bloki_z_pliku(char *nazwa_pliku);

void zapisz_do_pliku(struct blok (*bloki)[ILOSC_BLOKOW], char *nazwa_pliku);

int main() {
    struct blok bloki[ILOSC_BLOKOW];
    char *teksty[ILOSC_BLOKOW] = {
            "ala ma kota",
            "tekst w bloku nr 2",
            "a to zawartosc bloku 3",
    };

    for (int i = 0; i < ILOSC_BLOKOW; i++) {
        int hash_pop = i == 0 ? 0 : bloki[i - 1].hasz;
        wypelnij_blok(&bloki[i], i + 1, hash_pop, teksty[i]);
        kopanie(&bloki[i]);
        wypisz(&bloki[i]);
    }

    zapisz_do_pliku(&bloki, NAZWA_PLIKU);
    printf("\nOdczytane z pliku:\n");
    wypisz_bloki_z_pliku(NAZWA_PLIKU);
}

void wypelnij_blok(struct blok *blok, uint16_t nr_bloku, uint16_t hash_pop, char *zawartosc) {
    blok->hasz = 0;
    blok->hasz_pop = hash_pop;
    blok->nonce = 0;
    blok->nr_bloku = nr_bloku;
    strcpy(blok->zawartosc, zawartosc);
}

void kopanie(struct blok *blok) {
    for (int i = 0; i < 256 * 256; i++) {
        blok->nonce = i;
        blok->hasz = 0;
        for (int j = 0; j < 53; j++) {
            blok->hasz += blok->hasz_pop;
            blok->hasz += blok->nonce;
            blok->hasz += blok->nr_bloku;
            for (int k = 0; blok->zawartosc[k]; k++) {
                blok->hasz += blok->zawartosc[k];
            }
            blok->hasz = blok->hasz % (256 * 256);
            blok->hasz++;
        }
        if (blok->hasz == blok->nr_bloku * 10) {
            return;
        }
    }
}

void wypisz(struct blok *blok) {
    printf("nr_bloku: %d\n", blok->nr_bloku);
    printf("\thasz: %d\n", blok->hasz);
    printf("\thasz_pop: %d\n", blok->hasz_pop);
    printf("\tnonce: %d\n", blok->nonce);
    printf("\tzawartosc: %s\n", blok->zawartosc);
}

void wypisz_bloki_z_pliku(char *nazwa_pliku) {
    struct blok blok;
    FILE *file = fopen(nazwa_pliku, "r");
    if (!file) {
        printf("Blad otwarcia\n");
        return;
    }
    while (1) {
        fread(&blok, sizeof(struct blok), 1, file);
        if (feof(file)) break;
        wypisz(&blok);
    }
    fclose(file);
}

void zapisz_do_pliku(struct blok (*bloki)[ILOSC_BLOKOW], char *nazwa_pliku) {
    FILE *file = fopen(nazwa_pliku, "w");
    if (!file) {
        printf("Blad otwarcia\n");
        return;
    }
    fwrite(bloki, sizeof(struct blok), ILOSC_BLOKOW, file);
    fclose(file);
}