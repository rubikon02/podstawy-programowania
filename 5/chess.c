#include <stdio.h>

#define WIN_SCORE 1000
#define LOSE_SCORE ( -1000 )
#define BOARD_SIZE 8
#define PIECES_COUNT 13
const char PIECE_LETTERS[] = {' ',
                              'P', 'S', 'G', 'W', 'H', 'K',
                              'p', 's', 'g', 'w', 'h', 'k'};
//const int PIECES[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
const int SCORES[] = {0,
                      1, 3, 4, 5, 9, WIN_SCORE,
                      -1, -3, -4, -5, -9, LOSE_SCORE};
const int VECTOR_COUNTS[] = {0,
                             3, 8, 4, 4, 8, 8,
                             3, 8, 4, 4, 8, 8};
#define DEPTH 6
#define MAX_MOVES 8
const int MAX_VECTOR_LENGTHS[] = {0,
                                  1, 1, BOARD_SIZE, BOARD_SIZE, BOARD_SIZE, 1,
                                  1, 1, BOARD_SIZE, BOARD_SIZE, BOARD_SIZE, 1};
const int WX[PIECES_COUNT][MAX_MOVES] = {
        {},
        {-1, 0,  1},
        {2,  2,  -2, -2, 1, -1, 1, -1},
        {1,  -1, 1,  -1},
        {1,  -1, 0,  0},
        {1,  -1, 1,  -1, 1, -1, 0, 0},
        {1,  -1, 1,  -1, 1, -1, 0, 0},
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
            score += SCORES[board[x][y]];
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
    int dummy;
    int score = get_board_score(board);
    if (score >= WIN_SCORE / 2 || score <= LOSE_SCORE / 2 || depth == 0) return score;
    if (depth % 2 == 0) {                   //ruch komputera
        int max_score = 100 * LOSE_SCORE;
        for (int x = 0; x < BOARD_SIZE; x++) {
            for (int y = 0; y < BOARD_SIZE; y++) {
                if (1 <= board[x][y] && board[x][y] <= 6) {
                    for (int vi = 0; vi < VECTOR_COUNTS[board[x][y]]; vi++) {
                        const int dx = WX[board[x][y]][vi];
                        const int dy = WY[board[x][y]][vi];
                        for (int v_len = 1; v_len <= MAX_VECTOR_LENGTHS[board[x][y]]; v_len++) {
                            const int dest_x = x + dx * v_len;
                            const int dest_y = y + dy * v_len;
                            if (!(0 <= dest_x && dest_x < BOARD_SIZE && 0 <= dest_y && dest_y < BOARD_SIZE)) continue;
                            if (board[dest_x][dest_y] == 0 || board[dest_x][dest_y] > 6) {
                                if (board[x][y] == 1 || board[x][y] == 7) {
                                    if (dest_x != x && v_len != 1) continue;
                                    if (dest_x != x && board[dest_x][dest_y] <= 6) continue;
                                    if (dest_x == x && v_len == 2 && ((board[x][y] == 1 && y == 1) || (board[x][y] == 7 && y == 6))) continue;
                                }
                                const int dest_field_content = board[dest_x][dest_y];
                                board[dest_x][dest_y] = board[x][y];
                                board[x][y] = 0;
                                score = best_move(board, depth - 1, &dummy, &dummy, &dummy, &dummy);
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
        return max_score;
    } else {                                //ruch gracza
        int min_score = 100 * WIN_SCORE;
        for (int x = 0; x < BOARD_SIZE; x++) {
            for (int y = 0; y < BOARD_SIZE; y++) {
                if (board[x][y] >= 7) {
                    for (int vi = 0; vi < VECTOR_COUNTS[board[x][y]]; vi++) {
                        const int dx = WX[board[x][y]][vi];
                        const int dy = WY[board[x][y]][vi];
                        for (int v_len = 1; v_len <= MAX_VECTOR_LENGTHS[board[x][y]]; v_len++) {
                            const int dest_x = x + dx * v_len;
                            const int dest_y = y + dy * v_len;
                            if (!(0 <= dest_x && dest_x < BOARD_SIZE && 0 <= dest_y && dest_y < BOARD_SIZE)) continue;
                            if (board[dest_x][dest_y] < 7) {
                                if (board[x][y] == 1 || board[x][y] == 7) {
                                    if (dest_x != x && v_len != 1) continue;
                                    if (dest_x != x && board[dest_x][dest_y] <= 6) continue;
                                    if (dest_x == x && v_len == 2 && ((board[x][y] == 1 && y == 1) || (board[x][y] == 7 && y == 6))) continue;
                                }
                                const int dest_field_content = board[dest_x][dest_y];
                                board[dest_x][dest_y] = board[x][y];
                                board[x][y] = 0;
                                score = best_move(board, depth - 1, &dummy, &dummy, &dummy, &dummy);
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
        return min_score;
    }
}


int main() {
    int board[BOARD_SIZE][BOARD_SIZE] = {
            {4, 1, 0, 0, 0, 0, 7, 10},
            {2, 1, 0, 0, 0, 0, 7, 8},
            {3, 1, 0, 0, 0, 0, 7, 9},
            {6, 1, 0, 0, 0, 0, 7, 12},
            {5, 1, 0, 0, 0, 0, 7, 11},
            {3, 1, 0, 0, 0, 0, 7, 9},
            {2, 1, 0, 0, 0, 0, 7, 8},
            {4, 1, 0, 0, 0, 0, 7, 10},
    };
//    int board[BOARD_SIZE][BOARD_SIZE] = {
//            {0, 0, 0, 0, 0, 0,  0, 0},
//            {0, 0, 0, 0, 0, 0,  0, 0},
//            {0, 0, 0, 0, 0, 0,  0, 0},
//            {0, 4, 0, 0, 0, 10, 0, 0},
//            {0, 0, 0, 0, 0, 0,  0, 0},
//            {0, 0, 0, 0, 0, 0,  0, 0},
//            {0, 0, 0, 0, 0, 0,  0, 0},
//            {0, 0, 0, 0, 0, 0,  0, 0},
//    };
    print_board(board);
    int from_x, from_y, to_x, to_y, score = 0;
    printf("\n");

    for (int curr_player = DEPTH % 2 == 0; score != WIN_SCORE && score != LOSE_SCORE; curr_player = !curr_player) {
        if (curr_player) {
            best_move(board, DEPTH, &from_x, &from_y, &to_x, &to_y);
        } else {
            printf("Podaj pozycje:");
            scanf("%d%d%d%d", &from_x, &from_y, &to_x, &to_y);
        }
        board[to_x][to_y] = board[from_x][from_y];
        board[from_x][from_y] = ' ';
        print_board(board);
        score = get_board_score(board);
        printf("%c[%d][%d]->[%d][%d], wynik: %d\n",
               PIECE_LETTERS[board[to_x][to_y]], from_x, from_y, to_x, to_y, score);
        if (score == WIN_SCORE) printf("Przegrales\n");
        if (score == LOSE_SCORE) printf("Wygrales\n");
        printf("\n");
    }
}