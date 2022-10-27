#include <stdio.h>

int find(const char source[], const char keyword[]) {
    for (int s = 0; source[s]; s++) {
        if (source[s] == keyword[0]) {
            int valid;
            for (int k = 0; keyword[k]; k++) {
                valid = keyword[k] == source[s + k];
            }
            if (valid) return s;
        }
    }
    return -1;
}

int main() {
    char tab1[] = "pewien tekst";
    char tab2[] = "tek";
    printf("%d", find(tab1, tab2));
}