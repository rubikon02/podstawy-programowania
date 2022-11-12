#include <stdio.h>

const int WIN_SCORE = 1000;
const int LOSE_SCORE = -1000;
const char COMPUTER_SYMBOL = 'x';
const char PLAYER_SYMBOL = 'o';

void fill(char board[3][3], char value) {
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            board[x][y] = value;
        }
    }
}

int check(char p[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (p[i][0] == COMPUTER_SYMBOL && p[i][1] == COMPUTER_SYMBOL && p[i][2] == COMPUTER_SYMBOL) return WIN_SCORE;
        if (p[0][i] == COMPUTER_SYMBOL && p[1][i] == COMPUTER_SYMBOL && p[2][i] == COMPUTER_SYMBOL) return WIN_SCORE;
        if (p[i][0] == COMPUTER_SYMBOL && p[1][1] == COMPUTER_SYMBOL && p[2 - i][2] == COMPUTER_SYMBOL) return WIN_SCORE;
        if (p[i][0] == PLAYER_SYMBOL && p[i][1] == PLAYER_SYMBOL && p[i][2] == PLAYER_SYMBOL) return LOSE_SCORE;
        if (p[0][i] == PLAYER_SYMBOL && p[1][i] == PLAYER_SYMBOL && p[2][i] == PLAYER_SYMBOL) return LOSE_SCORE;
        if (p[i][0] == PLAYER_SYMBOL && p[1][1] == PLAYER_SYMBOL && p[2 - i][2] == PLAYER_SYMBOL) return LOSE_SCORE;
    }
    return 0;
}

void print_board(char board[3][3]) {
    for (int x = 0; x < 5; x++) {
        if (x % 2) {
            printf(" - + - + - \n");
        } else {
            for (int y = 0; y < 5; y++) {
                if (y % 2) {
                    printf("|");
                } else {
                    printf(" %c ", board[x / 2][y / 2]);
                }
            }
            printf("\n");
        }
    }
}


int best_move(char board[3][3], int *best_x, int *best_y, int is_max) {
    int no_move = 1;
    int score = check(board);
    if (score) return score;
    if (is_max) {                   //ruch komputera
        int max_score = 2 * LOSE_SCORE;
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                if (board[x][y] == ' ') {
                    no_move = 0;
                    board[x][y] = COMPUTER_SYMBOL;
                    score = best_move(board, best_x, best_y, 0);
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
                    board[x][y] = PLAYER_SYMBOL;
                    score = best_move(board, best_x, best_y, 1);
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
    fill(board, ' ');
    int x, y;
    int score = 0;
    while (1) {
        best_move(board, &x, &y, 1);
        board[x][y] = COMPUTER_SYMBOL;
        printf("Komputer postawil %c na polu %d, %d\n", COMPUTER_SYMBOL, x, y);
        print_board(board);
        score = check(board);
        if (score == WIN_SCORE) printf("Przegrales\n");
        if (score == LOSE_SCORE) printf("Wygrales\n");
        if (score) return 0;
        printf("Podaj ruch:\n");
        scanf("%d%d",&x,&y);
        board[y][x] = PLAYER_SYMBOL;
        printf("Postawiles %c na polu %d, %d\n", PLAYER_SYMBOL, x, y);
        print_board(board);
        score = check(board);
        if (score == WIN_SCORE) printf("Przegrales\n");
        if (score == LOSE_SCORE) printf("Wygrales\n");
        if (score) return 0;
    }
}