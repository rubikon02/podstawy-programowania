#include <stdio.h>
#include <string.h>

int main() {
    size_t len = strlen("abcdefghi");
//    8 -> 0
//    for (int i = len - 1; i >= 0; --i) {
//        printf("%d\n", i);
//    }

//    8 -> 0
    for (size_t i = len - 1; i < len; --i) {
        printf("%d\n", i);
    }

}