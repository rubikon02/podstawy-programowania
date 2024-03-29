#include <stdio.h>
#include <time.h>

#define DEPTH 5
#define CHECK_PLAYER_MOVES 1

#define WIN_SCORE 1000
#define LOSE_SCORE ( -1000 )
#define BOARD_SIZE 8
#define PIECES_COUNT 13
#define EMPTY 0
#define COMPUTER_PAWN 1
#define PLAYER_PAWN 7
#define MAX_MOVES 8

const char PIECE_LETTERS[] = {' ',
                              'P', 'S', 'G', 'W', 'H', 'K',
                              'p', 's', 'g', 'w', 'h', 'k'};
const int SCORES[] = {0,
                      1, 3, 4, 5, 9, WIN_SCORE,
                      -1, -3, -4, -5, -9, LOSE_SCORE};
const int VECTOR_COUNTS[] = {0,
                             3, 8, 4, 4, 8, 8,
                             3, 8, 4, 4, 8, 8};
const int MAX_VECTOR_LENGTHS[] = {0,
                                  2, 1, BOARD_SIZE, BOARD_SIZE, BOARD_SIZE, 1,
                                  2, 1, BOARD_SIZE, BOARD_SIZE, BOARD_SIZE, 1};
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
        {-1, -1,  -1},
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
    printf("   ");
    for (char x = 'a'; x < 'a' + BOARD_SIZE; x++) {
        printf("  %c ", x);
    }
    printf("\n");
    for (int y = 0; y < BOARD_SIZE * 2 + 1; y++) {
        if (y % 2) {
            printf(" %d ", (y - 1) / 2 + 1);
            for (int x = 0; x < BOARD_SIZE * 2 + 1; x++) {
                if (x % 2) {
                    printf(" %c ", PIECE_LETTERS[board[x / 2][y / 2]]);
                } else {
                    printf("|");
                }
            }
            printf(" %d\n", (y - 1) / 2 + 1);
        } else {
            printf("   ");
            for (int i = 0; i < BOARD_SIZE * 4 + 1; i++) {
                printf("-");
            }
            printf("\n");
        }
    }
    printf("   ");
    for (char x = 'a'; x < 'a' + BOARD_SIZE; x++) {
        printf("  %c ", x);
    }
    printf("\n");
}

float best_move(int board[BOARD_SIZE][BOARD_SIZE], int is_maximizing, int depth, float alpha, float beta, int *from_x, int *from_y, int *to_x, int *to_y) {
    int dummy;
    float score = (float)get_board_score(board);
    if (score >= WIN_SCORE / 2.0 || score <= LOSE_SCORE / 2.0 || depth == 0) return score;
    if (is_maximizing) {                   //ruch komputera
        float max_score = 100 * LOSE_SCORE;
        for (int x = 0; x < BOARD_SIZE; x++) {
            for (int y = 0; y < BOARD_SIZE; y++) {
                if (!(1 <= board[x][y] && board[x][y] <= 6)) continue;
                for (int vi = 0; vi < VECTOR_COUNTS[board[x][y]]; vi++) {
                    const int dx = WX[board[x][y]][vi];
                    const int dy = WY[board[x][y]][vi];
                    for (int v_len = 1; v_len <= MAX_VECTOR_LENGTHS[board[x][y]]; v_len++) {
                        const int dest_x = x + dx * v_len;
                        const int dest_y = y + dy * v_len;
                        if (!(0 <= dest_x && dest_x < BOARD_SIZE && 0 <= dest_y && dest_y < BOARD_SIZE)) continue;
                        if (board[dest_x][dest_y] == EMPTY || board[dest_x][dest_y] >= 7) {
                            if (board[x][y] != COMPUTER_PAWN
                            || (dx != 0 && v_len == 1 && board[dest_x][dest_y] >= 7)
                            || (dx == 0 && board[dest_x][dest_y] == EMPTY && (v_len == 1 || y == 1))
                            ) {
                                const int dest_field_content = board[dest_x][dest_y];
                                board[dest_x][dest_y] = board[x][y];
                                board[x][y] = EMPTY;
                                if (board[dest_x][dest_y] == COMPUTER_PAWN && dest_y == 7) {
                                    board[dest_x][dest_y] += 4;
                                }
                                score = best_move(board, 0, depth - 1, alpha, beta, &dummy, &dummy, &dummy, &dummy);
                                board[x][y] = board[dest_x][dest_y];
                                board[dest_x][dest_y] = dest_field_content;
                                score -= (float)(DEPTH - depth) / DEPTH;
                                if (score > max_score) {
                                    max_score = score;
                                    *from_x = x;
                                    *from_y = y;
                                    *to_x = dest_x;
                                    *to_y = dest_y;
                                }
                                alpha = max_score > alpha ? max_score : alpha;
                                if (max_score >= beta) break;
                            }
                        }
                        if (board[dest_x][dest_y]) break;
                    }
                }
            }
        }
        return max_score;
    } else {                                //ruch gracza
        float min_score = 100 * WIN_SCORE;
        for (int x = 0; x < BOARD_SIZE; x++) {
            for (int y = 0; y < BOARD_SIZE; y++) {
                if (board[x][y] < 7) continue;
                for (int vi = 0; vi < VECTOR_COUNTS[board[x][y]]; vi++) {
                    const int dx = WX[board[x][y]][vi];
                    const int dy = WY[board[x][y]][vi];
                    for (int v_len = 1; v_len <= MAX_VECTOR_LENGTHS[board[x][y]]; v_len++) {
                        const int dest_x = x + dx * v_len;
                        const int dest_y = y + dy * v_len;
                        if (!(0 <= dest_x && dest_x < BOARD_SIZE && 0 <= dest_y && dest_y < BOARD_SIZE)) continue;
                        if (board[dest_x][dest_y] < 7) {
                            if (board[x][y] != PLAYER_PAWN
                            || (dx != 0 && v_len == 1 && 1 <= board[dest_x][dest_y] && board[dest_x][dest_y] <= 6)
                            || (dx == 0 && board[dest_x][dest_y] == EMPTY && (v_len == 1 || y == 6))
                            ) {
                                const int dest_field_content = board[dest_x][dest_y];
                                board[dest_x][dest_y] = board[x][y];
                                board[x][y] = EMPTY;
                                if (board[dest_x][dest_y] == PLAYER_PAWN && dest_y == 0) {
                                    board[dest_x][dest_y] += 4;
                                }
                                score = best_move(board, 1, depth - 1, alpha, beta, &dummy, &dummy, &dummy, &dummy);
                                board[x][y] = board[dest_x][dest_y];
                                board[dest_x][dest_y] = dest_field_content;
                                score += (float)(DEPTH - depth) / DEPTH;
                                if (score < min_score) {
                                    min_score = score;
                                    *from_x = x;
                                    *from_y = y;
                                    *to_x = dest_x;
                                    *to_y = dest_y;
                                }
                                beta = min_score < beta ? min_score : beta;
                                if (min_score <= alpha) break;
                            }
                        }
                        if (board[dest_x][dest_y]) break;
                    }
                }
            }
        }
        return min_score;
    }
}

int is_player_move_valid(int board[BOARD_SIZE][BOARD_SIZE], int from_x, int from_y, int to_x, int to_y) {
    if (!(0 <= to_x && to_x < BOARD_SIZE && 0 <= to_y && to_y < BOARD_SIZE)) return 0;
    if (board[from_x][from_y] <= 6) return 0;

    int dummy;
    const int dest_field_content = board[to_x][to_y];
    board[to_x][to_y] = board[from_x][from_y];
    board[from_x][from_y] = EMPTY;
    float score = best_move(board, 1, 1, 100 * LOSE_SCORE, 100 * WIN_SCORE, &dummy, &dummy, &dummy, &dummy);
    board[from_x][from_y] = board[to_x][to_y];
    board[to_x][to_y] = dest_field_content;

    if (score > WIN_SCORE / 2.0) return 0;

    int move_found = 0;
    for (int vi = 0; vi < VECTOR_COUNTS[board[from_x][from_y]]; vi++) {
        const int dx = WX[board[from_x][from_y]][vi];
        const int dy = WY[board[from_x][from_y]][vi];
        for (int v_len = 1; v_len <= MAX_VECTOR_LENGTHS[board[from_x][from_y]]; v_len++) {
            const int dest_x = from_x + dx * v_len;
            const int dest_y = from_y + dy * v_len;
            if (dest_x == to_x && dest_y == to_y) {
                if (board[dest_x][dest_y] < 7) {
                    if (board[from_x][from_y] != PLAYER_PAWN
                        || (dx != 0 && v_len == 1 && 1 <= board[dest_x][dest_y] && board[dest_x][dest_y] <= 6)
                        || (dx == 0 && board[dest_x][dest_y] == EMPTY && (v_len == 1 || from_y == 6))
                    ) {
                        move_found = 1;
                    }
                }
            }
            if (board[dest_x][dest_y]) break;
        }
    }
    return move_found;
}

int main() {
    int board[BOARD_SIZE][BOARD_SIZE] = {       //zwykła plansza
            {4, 1, 0, 0, 0, 0, 7, 10},
            {2, 1, 0, 0, 0, 0, 7, 8},
            {3, 1, 0, 0, 0, 0, 7, 9},
            {6, 1, 0, 0, 0, 0, 7, 12},
            {5, 1, 0, 0, 0, 0, 7, 11},
            {3, 1, 0, 0, 0, 0, 7, 9},
            {2, 1, 0, 0, 0, 0, 7, 8},
            {4, 1, 0, 0, 0, 0, 7, 10},
    };
//    int board[BOARD_SIZE][BOARD_SIZE] = {       //komputer może zrobić szach mat
//            {6, 0, 0, 0, 0, 0,  0, 0},
//            {0, 0, 0, 0, 0, 0,  0, 0},
//            {0, 0, 0, 0, 0, 0,  0, 0},
//            {0, 0, 0, 4, 0, 0, 0, 0},
//            {4, 4, 0, 4, 4, 0,  0, 0},
//            {0, 0, 0, 0, 0, 0,  0, 0},
//            {0, 0, 0, 0, 0, 0,  0, 0},
//            {0, 0, 12, 0, 0, 0,  0, 0},
//    };
//    int board[BOARD_SIZE][BOARD_SIZE] = {       //gracz może zrobić szach mat na d4d3
//            {12, 0, 0, 0, 0, 0,  0, 0},
//            {0, 0, 0, 0, 0, 0,  0, 0},
//            {0, 0, 0, 0, 0, 0,  0, 0},
//            {0, 0, 0, 10, 0, 0, 0, 0},
//            {10, 10, 0, 10, 10, 0,  0, 0},
//            {0, 0, 0, 0, 0, 0,  0, 0},
//            {0, 0, 0, 0, 0, 0,  0, 0},
//            {0, 0, 6, 0, 0, 0,  0, 0},
//    };
//    int board[BOARD_SIZE][BOARD_SIZE] = {       //gracz nie może ruszyć się królem na g3f3 pod szach
//            {6, 0, 0, 0, 0, 0,  0, 0},
//            {0, 0, 0, 0, 0, 0,  0, 0},
//            {0, 0, 0, 0, 0, 0,  0, 0},
//            {0, 0, 0, 0, 0, 0, 0, 0},
//            {4, 4, 0, 4, 4, 4,  0, 0},
//            {0, 0, 0, 0, 0, 0,  0, 0},
//            {0, 0, 12, 0, 0, 0,  0, 0},
//            {0, 0, 0, 0, 0, 0,  0, 0},
//    };
//    int board[BOARD_SIZE][BOARD_SIZE] = {       //brak ruchu
//            {12, 0, 0, 0, 0, 0,  0, 0},
//            {0, 0, 0, 0, 0, 0,  0, 4},
//            {0, 0, 0, 0, 0, 0,  0, 4},
//            {0, 0, 0, 0, 0, 0, 0, 4},
//            {0, 0, 0, 0, 0, 0,  4, 0},
//            {0, 0, 0, 0, 0, 0,  0, 0},
//            {0, 0, 0, 0, 0, 0,  0, 0},
//            {6, 0, 0, 0, 0, 0,  0, 0},
//    };

    int from_x, from_y, to_x, to_y, dummy;
    float score;
    char input[4];

    printf("Glebokosc sprawdzania %d\n", DEPTH);
    printf("Sprawdzanie poprawnosci ruchow gracza %d\n", CHECK_PLAYER_MOVES);
    printf("Podawaj ruchy w formacie e7e5\n");
    printf("\n");
    print_board(board);
    printf("\n");

    for (int curr_player = 1;; curr_player = !curr_player) {
        if (curr_player) {
            printf("Komputer mysli...\n");
            clock_t begin = clock();
            best_move(board, 1, DEPTH, 100 * LOSE_SCORE, 100 * WIN_SCORE, &from_x, &from_y, &to_x, &to_y);
            clock_t end = clock();
            double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
            printf("Ruch zajal %.2fs\n", time_spent);

        } else {
            printf("Podaj ruch:");
            scanf("%s", input);
            from_x = input[0] - 'a';
            to_x = input[2] - 'a';
            from_y = input[1] - '0' - 1;
            to_y = input[3] - '0' - 1;

            while (CHECK_PLAYER_MOVES && !is_player_move_valid(board, from_x, from_y, to_x, to_y)) {
                printf("Podaj poprawny ruch:");
                scanf("%s", input);
                from_x = input[0] - 'a';
                to_x = input[2] - 'a';
                from_y = input[1] - '0' - 1;
                to_y = input[3] - '0' - 1;
            }
        }
        board[to_x][to_y] = board[from_x][from_y];
        if ((board[to_x][to_y] == COMPUTER_PAWN && to_y == 7) || (board[to_x][to_y] == PLAYER_PAWN && to_y == 0)) {
            board[to_x][to_y] += 4;
            printf("Pionek zostal zamieniony na hetmana\n");
        }
        board[from_x][from_y] = EMPTY;
        score = (float)get_board_score(board);
        printf("%c %c%d->%c%d, wynik: %d\n", PIECE_LETTERS[board[to_x][to_y]], from_x + 'a', from_y + 1, to_x + 'a', to_y + 1, (int)score);
        print_board(board);
        score = best_move(board, !curr_player, 2, 100 * LOSE_SCORE, 100 * WIN_SCORE, &dummy, &dummy, &dummy, &dummy);
        if (score > WIN_SCORE / 2.0) { printf("Przegrales\n"); return 0; }
        if (score < LOSE_SCORE / 2.0) { printf("Wygrales\n"); return 0; }
        printf("\n");
    }
}