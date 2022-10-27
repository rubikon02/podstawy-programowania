#include <stdio.h>
#include <string.h>

void reverse(char text[]) {
    size_t len = strlen(text);

    char result[len + 1];

    int result_i = 0;
    for (size_t i = len - 1; i <= len; i--) {
        if (text[i] == ' ' || i == 0) {
            for (int j = !i ? 0 : 1; text[i + j] && text[i + j] != ' '; j++) {
                result[result_i++] = text[i + j];
            }
            if (i) {
                result[result_i++] = ' ';
            }
        }
    }
    result[len] = '\0';
    strcpy(text, result);
}

int main() {
    char letters[] = "wyraz1 wyraz2 wyraz3 wyraz1231 wyrazabc";
    reverse(letters);
    printf("%s", letters);
}