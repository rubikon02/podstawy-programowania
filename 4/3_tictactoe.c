#include <stdio.h>

const int WIN_SCORE = 1000;
const int LOSE_SCORE = -1000;

int check(char p[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (p[i][0] == 'x' && p[i][1] == 'x' && p[i][2] == 'x') return WIN_SCORE;
        if (p[0][i] == 'x' && p[1][i] == 'x' && p[2][i] == 'x') return WIN_SCORE;
        if (p[i][0] == 'x' && p[1][1] == 'x' && p[2 - i][2] == 'x') return WIN_SCORE;
        if (p[i][0] == 'o' && p[i][1] == 'o' && p[i][2] == 'o') return LOSE_SCORE;
        if (p[0][i] == 'o' && p[1][i] == 'o' && p[2][i] == 'o') return LOSE_SCORE;
        if (p[i][0] == 'o' && p[1][1] == 'o' && p[2 - i][2] == 'o') return LOSE_SCORE;
    }
    return 0;
}

void print_board(char board[3][3]) {
    for (int y = 0; y < 5; y++) {
        if (y % 2) {
            printf(" - + - + - \n");
        } else {
            for (int x = 0; x < 5; x++) {
                if (x % 2) {
                    printf("|");
                } else {
                    printf(" %c ", board[x / 2][y / 2]);
                }
            }
            printf("\n");
        }
    }
}


int best_move(char board[3][3], int depth, int *best_x, int *best_y) {
    int no_move = 1;
    int new_x, new_y;
    int score = check(board);
    if (depth == 0 || score != 0) return score;
    if (depth % 2 == 0) {                   //ruch komputera
        int max_score = 2 * LOSE_SCORE;
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                if (board[x][y] == ' ') {
                    no_move = 0;
                    board[x][y] = 'x';
                    score = best_move(board, depth - 1, &new_x, &new_y);
                    board[x][y] = ' ';
                    if (score > max_score) {
                        max_score = score;
                        *best_x = x;
                        *best_y = y;
                    }
                }
            }
        }
        return no_move ? 0 : max_score;
    } else {                                //ruch gracza
        int min_score = 2 * WIN_SCORE;
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                if (board[x][y] == ' ') {
                    no_move = 0;
                    board[x][y] = 'o';
                    score = best_move(board, depth - 1, &new_x, &new_y);
                    board[x][y] = ' ';
                    if (score < min_score) {
                        min_score = score;
                        *best_x = x;
                        *best_y = y;
                    }
                }
            }
        }
        return no_move ? 0 : min_score;
    }
}

int main() {
    char board[3][3];
    for (int x = 0; x < 3; x++) for (int y = 0; y < 3; y++) board[x][y] = ' ';
    int x, y, score, move = 0;
    while (1) {
        best_move(board, 10, &x, &y);
        board[x][y] = 'x';
        print_board(board);
        score = check(board);
        if (score == WIN_SCORE) printf("Przegrales\n");
        if (score == LOSE_SCORE) printf("Wygrales\n");
        if (score || move++ == 4) return 0;
        printf("Podaj pozycje:");
        scanf("%d%d",&x,&y);
        board[x][y] = 'o';
        print_board(board);
        score = check(board);
        if (score == WIN_SCORE) printf("Przegrales\n");
        if (score == LOSE_SCORE) printf("Wygrales\n");
        if (score) return 0;
    }
}