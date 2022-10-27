#include <stdio.h>

void strcpy1(char dokad[], const char skad[]){
    for (int i = 0; (dokad[i] = skad[i]); i++);
}

int strlen1(const char tab[]){
    int len = 0;
    for (;tab[len++];);
    return len;
}

void strcat1(char dokad[], const char skad[]){
    int i, j;
    for (i = 0; dokad[i]; i++);
    for (j = 0; (dokad[j + i] = skad[j]); j++);
}

int strcmp1(const char tab1[], const char tab2[]){
    for (int i = 0; tab1[i++];) {
        if (tab1[i] != tab2[i]) {
            return 0;
        }
    }
    return 1;
}


int main() {
    char tab1[100] = "pewien tekst";
    char tab2[100];

    strcpy1(tab2, tab1);
    printf("%s", tab2);

}

