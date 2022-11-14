#include <stdio.h>

const int WIN_SCORE = 1000;
const int LOSE_SCORE = -1000;
const char COMPUTER_SYMBOL = 'x';
const char PLAYER_SYMBOL = 'o';
const char BOARD_SIZE = 3;
const char WINNING_COUNT = 3;


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
    printf("%d x z rzedu, %d y z rzedu\n", most_consecutive_computer, most_consecutive_player);
    return most_consecutive_computer - most_consecutive_player;
    return 0;
}

void print_solution(char tab[3][3]) {
    \
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            printf("%c ", tab[y][x]);
        }
        printf("\n");
    }
    int score = check(tab);
    printf("wynik: %d\n-----\n", score);

//    if (score > 0) {
//        printf("x wygrywa\n");
//    } else if (score < 0) {
//        printf("o wygrywa\n");
//    } else {
//        printf("remis\n");
//    }
}

int main(void) {
    char tab1[3][3] = {{' ', ' ', 'o'},
                       {' ', 'o', ' '},
                       {'o', ' ', ' '}};
    print_solution(tab1);
    char tab2[3][3] = {{' ', 'o', ' '},
                       {'x', ' ', 'o'},
                       {'x', 'o', 'o'}};
    print_solution(tab2);
}