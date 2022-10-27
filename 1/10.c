//choinka pojedyncza o podanym rozmiarze z gwiazdek

#include <stdio.h>

int main(void) {
    int count;
    scanf("%d", &count);
//    1 sposób
//    for (int line = 0; line < count; line++) {
//        for (int j = count - line - 1; j > 0; j--) {
//            printf(" ");
//        }
//        for (int j = 0; j < 2 * line + 1; j++) {
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