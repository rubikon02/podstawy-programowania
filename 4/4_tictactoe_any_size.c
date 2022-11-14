#include <stdio.h>

const int WIN_SCORE = 1000;
const int LOSE_SCORE = -1000;
const char COMPUTER_SYMBOL = 'x';
const char PLAYER_SYMBOL = 'o';
const char BOARD_SIZE = 10;
const char WINNING_COUNT = 5;
const char DEPTH = 3;

void fill(char board[BOARD_SIZE][BOARD_SIZE], char value) {
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            board[x][y] = value;
        }
    }
}

int check(char p[BOARD_SIZE][BOARD_SIZE]) {
    int consecutive_computer, consecutive_player;
    int most_consecutive_computer = 0, most_consecutive_player = 0;
    for (int x = 0; x < BOARD_SIZE; x++) {
        consecutive_computer = 0, consecutive_player = 0;
        for (int y = 0; y < BOARD_SIZE; y++) {
            consecutive_player = p[x][y] == PLAYER_SYMBOL ? consecutive_player + 1 : 0;
            consecutive_computer = p[x][y] == COMPUTER_SYMBOL ? consecutive_computer + 1 : 0;
            if (consecutive_player >= WINNING_COUNT) return LOSE_SCORE;
            if (consecutive_computer >= WINNING_COUNT) return WIN_SCORE;
        }
        if (consecutive_computer > most_consecutive_computer) most_consecutive_computer = consecutive_computer;
        if (consecutive_player > most_consecutive_player) most_consecutive_player = consecutive_player;
        consecutive_computer = 0, consecutive_player = 0;
        for (int y = 0; y < BOARD_SIZE; y++) {
            consecutive_player = p[y][x] == PLAYER_SYMBOL ? consecutive_player + 1 : 0;
            consecutive_computer = p[y][x] == COMPUTER_SYMBOL ? consecutive_computer + 1 : 0;
            if (consecutive_player >= WINNING_COUNT) return LOSE_SCORE;
            if (consecutive_computer >= WINNING_COUNT) return WIN_SCORE;
        }
        if (consecutive_computer > most_consecutive_computer) most_consecutive_computer = consecutive_computer;
        if (consecutive_player > most_consecutive_player) most_consecutive_player = consecutive_player;
        consecutive_computer = 0, consecutive_player = 0;
        for (int y = 0; y < BOARD_SIZE; y++) {
            if (!p[x + y][y]) continue;
            consecutive_player = p[x + y][y] == PLAYER_SYMBOL ? consecutive_player + 1 : 0;
            consecutive_computer = p[x + y][y] == COMPUTER_SYMBOL ? consecutive_computer + 1 : 0;
            if (consecutive_player >= WINNING_COUNT) return LOSE_SCORE;
            if (consecutive_computer >= WINNING_COUNT) return WIN_SCORE;
        }
        if (consecutive_computer > most_consecutive_computer) most_consecutive_computer = consecutive_computer;
        if (consecutive_player > most_consecutive_player) most_consecutive_player = consecutive_player;
        consecutive_computer = 0, consecutive_player = 0;
        for (int y = 0; y < BOARD_SIZE; y++) {
            if (!p[BOARD_SIZE - 1 - x - y][y]) continue;
            if (p[BOARD_SIZE - 1 - x - y][y] == COMPUTER_SYMBOL) consecutive_computer++;
            else consecutive_computer = 0;
            if (p[BOARD_SIZE - 1 - x - y][y] == PLAYER_SYMBOL) consecutive_player++;
            else consecutive_player = 0;
            if (consecutive_player >= WINNING_COUNT) return LOSE_SCORE;
            if (consecutive_computer >= WINNING_COUNT) return WIN_SCORE;
        }
        if (consecutive_computer > most_consecutive_computer) most_consecutive_computer = consecutive_computer;
        if (consecutive_player > most_consecutive_player) most_consecutive_player = consecutive_player;
    }
    return most_consecutive_computer - most_consecutive_player;
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
    if (score == WIN_SCORE || score == LOSE_SCORE || depth == 0) return score;
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
        if (depth == DEPTH) {
            printf("Zwrocony wynik: %d\n", no_move ? 0 : max_score);
        }
        return no_move ? 0 : max_score;
    } else {                                //ruch gracza
        int min_score = 2 * WIN_SCORE;
        for (int x = 0; x < BOARD_SIZE; x++) {
            for (int y = 0; y < BOARD_SIZE; y++) {
                if (board[x][y] == ' ') {
                    no_move = 0;
                    board[x][y] = PLAYER_SYMBOL;
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
        if (depth == DEPTH) {
            printf("Zwrocony wynik: %d\n", no_move ? 0 : min_score);
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
        best_move(board, DEPTH, &x, &y);
        board[x][y] = COMPUTER_SYMBOL;
        printf("Komputer postawil %c na polu %d, %d\n", COMPUTER_SYMBOL, x, y);
        print_board(board);
        score = check(board);
        if (score == WIN_SCORE) {
            printf("Przegrales\n");
            return 0;
        }
        if (score == LOSE_SCORE) {
            printf("Wygrales\n");
            return 0;
        }
        printf("Podaj ruch:");
        scanf("%d%d", &x, &y);
        board[x][y] = PLAYER_SYMBOL;
        printf("Postawiles %c na polu %d, %d\n", PLAYER_SYMBOL, x, y);
        print_board(board);
        score = check(board);
        if (score == WIN_SCORE) {
            printf("Przegrales\n");
            return 0;
        }
        if (score == LOSE_SCORE) {
            printf("Wygrales\n");
            return 0;
        }
    }
}