#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define OCENA  0
#define STR_MAX 1024
#define SIZE_BUF 80

struct Word {
    char *word;
    int number_of_rep;
};

int cmpfun(struct Word *a, struct Word *b){
    return strcmp((*(char**)(a->word)),(*(char**)(b->word)));
}
int cmpfun2(char **klucz, struct Word **slowo){
    printf("Porownoje %s z %s\n", *klucz, (*slowo)->word);
    return strcmp(*klucz,(*slowo)->word);
}


int main(void) {
    fflush(stdout);
    int repet_no;        // numer wyrazu liczona wg liczby powtórzeń
    char buffer[SIZE_BUF];
    struct Word *str_tab[STR_MAX];
    for (int i = 0; i < STR_MAX; i++) {
//        str_tab[i] = 0;
        str_tab[i] = malloc(sizeof(struct Word));
        str_tab[i]->word = "temp";
        str_tab[i]->number_of_rep = 0;
    }
    int tab_size = 0;
    FILE *plik;
    plik = OCENA ? fopen("tekst_linux.txt","r") : stdin;
    if(plik==NULL) { printf("Blad w fopen\n");  exit(1); }

    do {
        char c = fgetc(plik);

        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '/' || c == '\'' || c == '-') {
            buffer[strlen(buffer)] = c;
        } else if ((c == ' ' || c == '\n') && strlen(buffer) > 0) {
            char *temp_string = (char *)malloc(strlen(buffer) + 1);
            strcpy(temp_string, buffer);
            printf("slowo ktore sprawdzam: %s\n", temp_string);
            struct Word *znaleziony = 0;
            if (tab_size)
                znaleziony = bsearch(&temp_string,str_tab,tab_size, sizeof(struct Word),(int(*)(const void *, const void *))cmpfun2);
            if(znaleziony){
                znaleziony->number_of_rep++;

            }else{
                struct Word *word = malloc(sizeof(struct Word));
                word->word = temp_string;
                word->number_of_rep = 0;
                str_tab[tab_size++] = word;
                printf("Wstawiam %s\n", word->word);
            }
            qsort(str_tab, tab_size, sizeof(struct Word),(int(*)(const void *, const void *))cmpfun);
            printf("Tablica:\n");
            for (int i = 0; i < tab_size; i++) {
                printf("%s\n", str_tab[i]->word);
            }
            memset(buffer, 0, sizeof buffer);
        }
    } while (!feof(plik));

    if(OCENA==0) printf("Który (liczac od 1) wyraz ma byc wyprowadzony na ekran (wg malejącej krotności wyrazow): ");
    scanf("%d",&repet_no);

    for(int i=0; i<STR_MAX; i++){
        printf("%s %d\n", str_tab[i]->word, str_tab[i]->number_of_rep);
    }


    return 0;
}