#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    char *str = (char *) malloc(10);
    strcpy(str, "1234567890");
    printf("%s\n", str);

//błąd
//    str++;
//    printf("%s\n", str);
//    free(str);

//poprawne
    char *str2 = (char *) malloc(9);
    strcpy(str2, str + 1);
    printf("%s\n", str2);
    free(str);
    free(str2);
}