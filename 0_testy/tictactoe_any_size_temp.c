#include <stdio.h>

const int WIN_SCORE = 1000;
const int LOSE_SCORE = -1000;
const char COMPUTER_SYMBOL = 'x';
const char PLAYER_SYMBOL = 'o';
const char BOARD_SIZE = 7;
const char WINNING_COUNT = 4;

void fill(char board[BOARD_SIZE][BOARD_SIZE], char value) {
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            board[x][y] = value;
        }
    }
}

//int check(char p[BOARD_SIZE][BOARD_SIZE]) {
//    for (int i = 0; i < 3; i++) {
//        if (p[i][0] == 'x' && p[i][1] == 'x' && p[i][2] == 'x') return WIN_SCORE;
//        if (p[0][i] == 'x' && p[1][i] == 'x' && p[2][i] == 'x') return WIN_SCORE;
//        if (p[i][0] == 'x' && p[1][1] == 'x' && p[2 - i][2] == 'x') return WIN_SCORE;
//        if (p[i][0] == 'o' && p[i][1] == 'o' && p[i][2] == 'o') return LOSE_SCORE;
//        if (p[0][i] == 'o' && p[1][i] == 'o' && p[2][i] == 'o') return LOSE_SCORE;
//        if (p[i][0] == 'o' && p[1][1] == 'o' && p[2 - i][2] == 'o') return LOSE_SCORE;
//    }
//    return 0;
//}

int check_in_direction(char p[BOARD_SIZE][BOARD_SIZE], int sx, int sy, int xdir, int ydir) {
    int dx = 0, dy = 0;
    int score = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (!p[sx + dx][sy + dy]) break;

        dx += xdir;
        dy += ydir;
    }
}

int check(char p[BOARD_SIZE][BOARD_SIZE]) {
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {

        }
    }
}

void print_board(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int y = 0; y < BOARD_SIZE * 2 - 1; y++) {
        if (y % 2) {
            for (int i = 0; i < BOARD_SIZE * 2 - 1; i++) {
                printf(i % 2 ? " +" : " -");
            }
            printf("\n");
        } else {
            for (int x = 0; x < BOARD_SIZE * 2 - 1; x++) {
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


int best_move(char board[BOARD_SIZE][BOARD_SIZE], int depth, int *best_x, int *best_y) {
    int no_move = 1;
    int new_x, new_y;

    int score = check(board);
//    printf("%d ", score);
    if (score != 0 || depth == 0) return score;
    if (depth % 2 == 0) {                   //ruch komputera
        int max_score = 2 * LOSE_SCORE;
        for (int x = 0; x < BOARD_SIZE; x++) {
            for (int y = 0; y < BOARD_SIZE; y++) {
                if (board[x][y] == ' ') {
                    no_move = 0;
                    board[x][y] = COMPUTER_SYMBOL;
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
        for (int x = 0; x < BOARD_SIZE; x++) {
            for (int y = 0; y < BOARD_SIZE; y++) {
                if (board[x][y] == ' ') {
                    no_move = 0;
                    board[x][y] = PLAYER_SYMBOL;
                    score = best_move(board, depth - 1, best_x, best_y);
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
    char board[BOARD_SIZE][BOARD_SIZE];
    fill(board, ' ');
    int x, y;
    x = 0;
    y = 0;
    int score = 0;
    while (1) {
        best_move(board, 4, &x, &y);
        board[x][y] = COMPUTER_SYMBOL;
        printf("Komputer postawil %c na polu %d, %d\n", COMPUTER_SYMBOL, x, y);
        print_board(board);
        score = check(board);
        if (score == WIN_SCORE) {printf("Przegrales\n"); return 0; }
        if (score == LOSE_SCORE) {printf("Wygrales\n"); return 0; }
        printf("Podaj ruch:");
        scanf("%d%d",&x,&y);
        board[x][y] = PLAYER_SYMBOL;
        printf("Postawiles %c na polu %d, %d\n", PLAYER_SYMBOL, x, y);
        print_board(board);
        score = check(board);
        if (score == WIN_SCORE) {printf("Przegrales\n"); return 0; }
        if (score == LOSE_SCORE) {printf("Wygrales\n"); return 0; }
    }
}