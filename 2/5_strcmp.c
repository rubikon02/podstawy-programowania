#include <stdio.h>

int main() {
    char tab1[100] = "pewien tekst";
    char tab2[100] = "pewien tekst";

    int same = 1;
    for (int i = 0; tab1[i++];) {
        if (tab1[i] != tab2[i]) {
            same = 0;
        }
    }

    printf("%d", same);
}