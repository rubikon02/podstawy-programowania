#include <stdio.h>

char capitalize(char letters[]) {
    for (int i = 0; letters[i]; i++) {
        if ('a' <= letters[i] && letters[i] <= 'z') {
            letters[i] += 'A' - 'a';
        }
    }
}

int main() {
    char letters[] = "abc12deF";
    capitalize(letters);
    printf("%s", letters);
}