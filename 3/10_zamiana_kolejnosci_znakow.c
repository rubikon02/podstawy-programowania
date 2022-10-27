#include <stdio.h>
#include <string.h>

void reverse(char words[]) {
    size_t size = strlen(words);
    
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