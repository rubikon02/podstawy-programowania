#include <stdio.h>

int main() {
    char tab1[100] = "pewien tekst";

    int len = 0;
    for (;tab1[len++];);

    printf("%d", len);
}