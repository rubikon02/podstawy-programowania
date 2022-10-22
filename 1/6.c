//wypisanie tyle liczb ile chce użytkownik

#include <stdio.h>

int main(void) {
    int count;
    scanf("%d", &count);
    for (int i = 0; i < count; i++) {
        printf("%d\n", i);
    }
}