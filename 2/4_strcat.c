#include <stdio.h>

int main() {
    char tab1[100] = "pewien tekst";
    char tab2[100] = "drugi tekst";

//    int len2 = 0;
//    for (;tab2[len2++];);
//
//    int i = 0;
//    do {
//        tab2[len2 - 1 + i] = tab1[i];
//    } while(tab1[i++]);

    int i, j;
    for (i = 0; tab2[i]; i++);
    for (j = 0; (tab2[j + i] = tab1[j]); j++);

    printf("%s", tab2);
}