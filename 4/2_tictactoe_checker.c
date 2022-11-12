#include <stdio.h>

int check(char p[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (p[i][0] == 'x' && p[i][1] == 'x' && p[i][2] == 'x') return 1;
        if (p[0][i] == 'x' && p[1][i] == 'x' && p[2][i] == 'x') return 1;
        if (p[i][0] == 'x' && p[1][1] == 'x' && p[2 - i][2] == 'x') return 1;
        if (p[i][0] == 'o' && p[i][1] == 'o' && p[i][2] == 'o') return -1;
        if (p[0][i] == 'o' && p[1][i] == 'o' && p[2][i] == 'o') return -1;
        if (p[i][0] == 'o' && p[1][1] == 'o' && p[2 - i][2] == 'o') return -1;
    }
    return 0;
}

void print_solution(char tab[3][3]) {
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            printf("%c ", tab[y][x]);
        }
        printf("\n");
    }
    int score = check(tab);
    if (score > 0) {
        printf("x wygrywa\n");
    } else if (score < 0) {
        printf("o wygrywa\n");
    } else {
        printf("remis\n");
    }
}

int main(void) {
    char tab1[3][3] = {{' ', ' ', 'o'},
                       {' ', 'o', ' '},
                       {'o', ' ', ' '}};
    print_solution(tab1);
    char tab2[3][3] = {{'x', 'o', ' '},
                       {'x', ' ', 'o'},
                       {'x', 'o', 'o'}};
    print_solution(tab2);
}