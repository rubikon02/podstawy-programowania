#include <stdio.h>

int search(const int tab[], int to_search) {
    for(int i = 0; tab[i]; i++) {
        if (tab[i] == to_search) {
            return i;
        }
    }
    return -1;
}

int main() {
    int tab[10] = {3, 4, 2, 7, 3, 5, 6, 7, 8, 9};
    int to_search;
    scanf("%d", &to_search);

//    printf("%d", search(tab, to_search));

    int i = search(tab, to_search);
    if (i == -1) {
        printf("Nie znaleziono\n");
    } else {
        printf("Wartosc %d znajduje sie pod indeksem %d\n", to_search, i);
    }
;}