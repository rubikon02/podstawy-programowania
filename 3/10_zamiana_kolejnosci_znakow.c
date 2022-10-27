#include <stdio.h>

void reverse(char words[]) {
    int size = 0;
    for (size = 0; words[size]; size++);

    for (int i = 0; i < size / 2; i++) {
        char t = words[i];
        words[i] = words[size - 1 - i];
        words[size - 1 - i] = t;
    }
}

int main() {
    char words[] = "abc123deF";
    reverse(words);
    printf("%s", words);
}