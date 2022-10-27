#include <stdio.h>

int main(void) {
    unsigned char t1[4] = {10, 11, 12, 13}, t2[4] = {20, 21, 22, 23};
    printf("%d %d\n", t1[6], t2[6]);
}