//pierwsze n liter alfabetu

#include <stdio.h>

int main(void) {
    int size;
    scanf("%d", &size);
    for (int i = 0; i < size; i++) {
        char letter = 'a' + i;
        printf("%c", letter);
    }
}
