#include <stdio.h>

int main() {
    char tab1[100] = "pewien tekst";
    char tab2[100];

//    int i = 0;
//    do {
//        tab2[i] = tab1[i];
//    } while(tab1[i++]);

//    int i;
//    for (i = 0; tab1[i]; i++) {
//        tab2[i] = tab1[i];
//    }
//    tab2[i] = tab1[i];

    for (int i = 0; (tab2[i] = tab1[i]); i++)

    printf("%s", tab2);
}

//void strcpy(char dokad[], char skad[]){
//
//}