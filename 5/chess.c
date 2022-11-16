#include <stdio.h>

#define WIN_SCORE 1000
#define LOSE_SCORE ( -1000 )
#define BOARD_SIZE 8
#define PIECES_COUNT 13
const char PIECE_LETTERS[] = {' ', 'P', 'S', 'G', 'W', 'H', 'K', 'p', 's', 'g', 'w', 'h', 'k'};
const int PIECES[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
const int SCORES[] = {0, 1, 3, 4, 5, 9, WIN_SCORE, -1, -3, -4, -5, -9, LOSE_SCORE};
const int PIECE_MOVE_DISTANCE[] = {0, 2, 1, -1, -1, -1, 1, 2, 1, -1, -1, -1, 1};
#define DEPTH 2
#define MAX_MOVES 8
const int MOVE_COUNTS[] = {0, 3, 8, 4, 4, 8, 8, 3, 8, 4, 4, 8, 8};
const int MAX_MOVE_DISTANCES[] = {1, 1, BOARD_SIZE, BOARD_SIZE, BOARD_SIZE, 1};
const int WX[PIECES_COUNT][MAX_MOVES] = {
        {},
        {-1, 0,  1},
        {2,  2,  -2, -2, 1, -1, 1, -1},
        {1,  -1, 1,  -1},
        {1,  -1, 0,  0},
        {1,  -1, 1,  -1, 1, -1, 0, 0},
        {1,  -1, 1,  -1, 1, -1, 0, 0},
};
const int WY[PIECES_COUNT][MAX_MOVES] = {
        {},
        {1, 1,  1},
        {1, -1, 1,  -1, 2, 2, -2, -2},
        {1, -1, -1, 1},
        {0, 0,  -1, 1},
        {1, -1, -1, 1,  0, 0, -1, 1},
        {1, -1, -1, 1,  0, 0, -1, 1},
};


int get_board_score(int board[BOARD_SIZE][BOARD_SIZE]) {
    int score = 0;
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            score += board[x][y];
        }
    }
    return score;
}

void print_board(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int x = 0; x < BOARD_SIZE; ++x) {
        printf("%d", x);
    }
    printf("\n");
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            printf("%c", PIECE_LETTERS[board[x][y]]);
        }
        printf(" %d\n", y);
    }
}

int best_move(int board[BOARD_SIZE][BOARD_SIZE], int depth, int *from_x, int *from_y, int *to_x, int *to_y) {
    int no_move = 1;
    int new_x, new_y;
    int new_x2, new_y2;
    int score = get_board_score(board);
    if (score == WIN_SCORE || score == LOSE_SCORE || depth == 0) return score;
    if (depth % 2 == 0) {                   //ruch komputera
        int max_score = 2 * LOSE_SCORE;
        for (int x = 0; x < BOARD_SIZE; x++) {
            for (int y = 0; y < BOARD_SIZE; y++) {
                if (1 <= board[x][y] && board[x][y] <= 6) {
                    for (int move_i = 0; move_i < MOVE_COUNTS[board[x][y]]; move_i++) {
                        const int dx = WX[board[x][y]][move_i];
                        const int dy = WY[board[x][y]][move_i];
                        for (int vectors_count = 1; vectors_count <= MAX_MOVE_DISTANCES[board[x][y]]; vectors_count++) {
                            const int dest_x = x + dx * vectors_count;
                            const int dest_y = y + dy * vectors_count;
                            if (0 <= dest_x && dest_x < BOARD_SIZE && 0 <= dest_y && dest_y < BOARD_SIZE) {
//                                ważne
//                                if (board[x][y] != 'p' || (board[x][y] == 'p' && (
//                                        (dest_x == x && board[dest_x][dest_y] == ' ') ||
//                                        (dest_x != x && board[dest_x][dest_y] != 0)
//                                ))) {
////                                ważne
//                                }
                                if (board[x][y] == ' ' || board[x][y] != board[dest_x][dest_y]) { //TOOOOOOO POPRAWIĆ
                                    no_move = 0;
                                    const int dest_field_content = board[dest_x][dest_y];
                                    board[dest_x][dest_y] = board[x][y];
                                    board[x][y] = ' ';
                                    score = best_move(board, depth - 1, &new_x2, &new_y2, &new_x, &new_y);
                                    board[x][y] = board[dest_x][dest_y];
                                    board[dest_x][dest_y] = dest_field_content;
                                    if (score > max_score) {
                                        max_score = score;
                                        *from_x = x;
                                        *from_y = y;
                                        *to_x = dest_x;
                                        *to_y = dest_y;
                                    }
                                }
                                if (board[dest_x][dest_y]) {
                                    break;
                                }
                            }
                        }
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
                if (board[x][y] > 6) {
                    for (int move_i = 0; move_i < MOVE_COUNTS[board[x][y]]; move_i++) {
                        const int dx = WX[board[x][y]][move_i];
                        const int dy = WY[board[x][y]][move_i];
                        for (int vectors_count = 1; vectors_count <= MAX_MOVE_DISTANCES[board[x][y]]; vectors_count++) {
                            const int dest_x = x + dx * vectors_count;
                            const int dest_y = y + dy * vectors_count;
                            if (0 <= dest_x && dest_x < BOARD_SIZE && 0 <= dest_y && dest_y < BOARD_SIZE) {
                                if (board[x][y] == ' ' || board[x][y] != board[dest_x][dest_y]) {
                                    no_move = 0;
                                    const int dest_field_content = board[dest_x][dest_y];
                                    board[dest_x][dest_y] = board[x][y];
                                    board[x][y] = ' ';
                                    score = best_move(board, depth - 1, &new_x2, &new_y2, &new_x, &new_y);
                                    board[x][y] = board[dest_x][dest_y];
                                    board[dest_x][dest_y] = dest_field_content;
                                    if (score < min_score) {
                                        min_score = score;
                                        *from_x = x;
                                        *from_y = y;
                                        *to_x = dest_x;
                                        *to_y = dest_y;
                                    }
                                }
                                if (board[dest_x][dest_y]) {
                                    break;
                                }
                            }
                        }
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
    int board[BOARD_SIZE][BOARD_SIZE] = {
            {4, 1, 0, 0, 0, 0, 7, 10},
            {2, 1, 0, 0, 0, 0, 7, 8},
            {3, 1, 0, 0, 0, 0, 7, 9},
            {5, 1, 0, 0, 0, 0, 7, 11},
            {6, 1, 0, 0, 0, 0, 7, 12},
            {3, 1, 0, 0, 0, 0, 7, 9},
            {2, 1, 0, 0, 0, 0, 7, 8},
            {4, 1, 0, 0, 0, 0, 7, 10},
    };
    print_board(board);
    int from_x, from_y, to_x, to_y, score;
    printf("Zaczynamy\n");

    while (1) {
        best_move(board, DEPTH, &from_x, &from_y, &to_x, &to_y);
        board[to_x][to_y] = board[from_x][from_y];
        printf("Komputer rusza sie z %d %d na %d %d\n", from_x, from_y, to_x, to_y);
        board[from_x][from_y] = ' ';
        print_board(board);
        score = get_board_score(board);
        if (score == WIN_SCORE) printf("Przegrales\n");
        if (score == LOSE_SCORE) printf("Wygrales\n");
        printf("Podaj pozycje:");
        scanf("%d%d%d%d", &from_x, &from_y, &to_x, &to_y);
        board[to_x][to_y] = board[from_x][from_y];
        board[from_x][from_y] = ' ';
        print_board(board);
        score = get_board_score(board);
        if (score == WIN_SCORE) printf("Przegrales\n");
        if (score == LOSE_SCORE) printf("Wygrales\n");
    }
}