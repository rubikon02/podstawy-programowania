//choinka pojedyncza o podanym rozmiarze z gwiazdek

#include <stdio.h>

int main(void) {
    int count;
    scanf("%d", &count);
//    1 sposób
//    for (int i = 0; i < count; i++) {
//        for (int j = count - i - 1; j > 0; j--) {
//            printf(" ");
//        }
//        for (int j = 0; j < 2 * i + 1; j++) {
//            printf("*");
//        }
//        printf("\n");
//    }
//    2 sposób
    for (int y = 0; y < count; y++) {
        for (int x = 0; x < count + y; x++) {
            printf(x >= count - y - 1 ? "*" : " ");
        }
        printf("\n");
    }
}