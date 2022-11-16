#include <stdio.h>

#define WIN_SCORE 1000
#define LOSE_SCORE ( -1000 )
#define BOARD_SIZE 8
#define PIECES_COUNT 6
const char PIECES[] = {'p', 's', 'g', 'w', 'h', 'k'};
const int PIECE_MOVE_DISTANCE[] = {2, 1, -1, -1, -1, 1};
const int SCORES[] = {1, 3, 4, 5, 9, WIN_SCORE};
#define DEPTH 2
#define MAX_MOVES 8
const int MOVE_COUNTS[] = {3, 8, 4, 4, 8, 8};
const int MAX_MOVE_DISTANCES[] = {1, 1, BOARD_SIZE, BOARD_SIZE, BOARD_SIZE, 1};
const int MOVES[PIECES_COUNT][MAX_MOVES][2] = {
        {
                {-1, 1},
                {0,  1},
                {1,  1}
        },
        {
                {2,  1},
                {2,  -1},
                {-2, 1},
                {-2, -1},
                {1, 2},
                {-1, 2},
                {1, -2},
                {-1, -2},
        },
        {
                {1,  1},
                {-1, -1},
                {1,  -1},
                {-1, 1},
        },
        {
                {1,  0},
                {-1, 0},
                {0,  -1},
                {0,  1},
        },
        {
                {1,  1},
                {-1, -1},
                {1,  -1},
                {-1, 1},
                {1, 0},
                {-1, 0},
                {0, -1},
                {0,  1},
        },
        {
                {1,  1},
                {-1, -1},
                {1,  -1},
                {-1, 1},
                {1, 0},
                {-1, 0},
                {0, -1},
                {0,  1},
        },
};

const int get_piece_index(char piece) {
    for (int i = 0; i < PIECES_COUNT; i++) {
        if (piece == PIECES[i] || piece == PIECES[i] - 'a' + 'A') {
            return i;
        }
    }
    return -1;
}

const int get_piece_owner(char piece) {
    if (piece == ' ') {
        return 0;
    } else if ('A' <= piece && piece <= 'Z') {
        return 1;
    } else {
        return -1;
    }
}

const int get_piece_score(char piece) {
    return piece == ' ' ? 0 : SCORES[get_piece_index(piece)] * get_piece_owner(piece);
}

void get_piece_moves(int moves[MAX_MOVES][2], char piece) {
    const int i = get_piece_index(piece);
    const int owner = get_piece_owner(piece);
    for (int x = 0; x < MOVE_COUNTS[i]; x++) {
        if (MOVES[i][x][0] == 0 && MOVES[i][x][1] == 0) {
            moves[x][0] = 0;
            moves[x][1] = 0;
        } else {
            moves[x][0] = MOVES[i][x][0];
            moves[x][1] = MOVES[i][x][1] * owner;
        }
    }
}

int get_board_score(char board[BOARD_SIZE][BOARD_SIZE]) {
    int score = 0;
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            score += get_piece_score(board[x][y]);
        }
    }
    return score;
}

void clear_board(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            board[x][y] = ' ';
        }
    }
}

void populate_board(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int x = 0; x < BOARD_SIZE; x++) {
        board[x][1] = 'P';
        board[x][BOARD_SIZE - 2] = 'p';
    }
    board[0][0] = 'W';
    board[1][0] = 'S';
    board[2][0] = 'G';
    board[3][0] = 'K';
    board[4][0] = 'H';
    board[5][0] = 'G';
    board[6][0] = 'S';
    board[7][0] = 'W';
    board[0][BOARD_SIZE - 1] = 'w';
    board[1][BOARD_SIZE - 1] = 's';
    board[2][BOARD_SIZE - 1] = 'g';
    board[3][BOARD_SIZE - 1] = 'k';
    board[4][BOARD_SIZE - 1] = 'h';
    board[5][BOARD_SIZE - 1] = 'g';
    board[6][BOARD_SIZE - 1] = 's';
    board[7][BOARD_SIZE - 1] = 'w';
}

void print_board(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int x = 0; x < BOARD_SIZE; ++x) {
        printf("%d", x);
    }
    printf("\n");
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            printf("%c", board[x][y]);
        }
        printf(" %d\n", y);
    }
}

int best_move(char board[BOARD_SIZE][BOARD_SIZE], int depth, int *from_x, int *from_y, int *to_x, int *to_y) {
    int no_move = 1;
    int new_x, new_y;
    int new_x2, new_y2;
    int score = get_board_score(board);
    if (score == WIN_SCORE || score == LOSE_SCORE || depth == 0) return score;
    if (depth % 2 == 0) {                   //ruch komputera
        int max_score = 2 * LOSE_SCORE;
        for (int x = 0; x < BOARD_SIZE; x++) {
            for (int y = 0; y < BOARD_SIZE; y++) {
                if (get_piece_owner(board[x][y]) == 1) {
                    int moves[MAX_MOVES][2];
                    const int piece_i = get_piece_index(board[x][y]);
                    get_piece_moves(moves, board[x][y]);
                    for (int move_i = 0; move_i < MOVE_COUNTS[piece_i]; move_i++) {
                        const int dx = moves[move_i][0];
                        const int dy = moves[move_i][1];
                        for (int vectors_count = 1; vectors_count <= MAX_MOVE_DISTANCES[piece_i]; vectors_count++) {
                            const int dest_x = x + dx * vectors_count;
                            const int dest_y = y + dy * vectors_count;
                            if (0 <= dest_x && dest_x < BOARD_SIZE && 0 <= dest_y && dest_y < BOARD_SIZE) {
                                const int source_owner = get_piece_owner(board[x][y]);
                                const int dest_owner = get_piece_owner(board[dest_x][dest_y]);
//                                ważne
                                if (board[x][y] != 'p' || (board[x][y] == 'p' && (
                                         (dest_x == x && board[dest_x][dest_y] == ' ') ||
                                         (dest_x != x && board[dest_x][dest_y] != 0)
                                    ))) {
//                                ważne
                                }
                                if (board[x][y] == ' ' || source_owner != dest_owner) {
                                    no_move = 0;
                                    const char dest_field_content = board[dest_x][dest_y];
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
                                if (dest_owner) {
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
                if (get_piece_owner(board[x][y]) == -1) {
                    int moves[MAX_MOVES][2];
                    int piece_i = get_piece_index(board[x][y]);
                    get_piece_moves(moves, board[x][y]);
                    for (int move_i = 0; move_i < MOVE_COUNTS[piece_i]; move_i++) {
                        const int dx = moves[move_i][0];
                        const int dy = moves[move_i][1];
                        for (int vectors_count = 1; vectors_count <= MAX_MOVE_DISTANCES[piece_i]; vectors_count++) {
                            const int dest_x = x + dx * vectors_count;
                            const int dest_y = y + dy * vectors_count;
                            if (0 <= dest_x && dest_x < BOARD_SIZE && 0 <= dest_y && dest_y < BOARD_SIZE) {
                                const int source_owner = get_piece_owner(board[x][y]);
                                const int dest_owner = get_piece_owner(board[dest_x][dest_y]);
                                if (board[x][y] == ' ' || source_owner != dest_owner) {
                                    no_move = 0;
                                    const char dest_field_content = board[dest_x][dest_y];
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
                                if (dest_owner) {
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
    char board[BOARD_SIZE][BOARD_SIZE];
    clear_board(board);
    populate_board(board);
    print_board(board);
    int from_x, from_y, to_x, to_y, score;
    printf("Zaczynamy\n");

    while (1) {
        best_move(board, DEPTH, &from_x, &from_y, &to_x, &to_y);
        board[to_x][to_y] = board[from_x][from_y];
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