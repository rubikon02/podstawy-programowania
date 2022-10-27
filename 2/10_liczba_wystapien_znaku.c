#include <stdio.h>

int count(const char tab[], const char letter) {
    int count = 0;
    for (int i = 0; tab[i]; i++) {
        count += tab[i] == letter;
    }
    return count;
}

int main() {
    char tab1[] = "pewien tekst";
    char letter;
    scanf("%c", &letter);
    printf("%d", count(tab1, letter));
}