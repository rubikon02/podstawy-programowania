#include <stdio.h>
#include <malloc.h>

#define WIN_SCORE 1000
#define LOSE_SCORE ( -1000 )
#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8
//const int BIGGEST_BOARD_SIZE = BOARD_WIDTH > BOARD_HEIGHT ? BOARD_WIDTH : BOARD_HEIGHT;
#define PIECES_COUNT 6
const char PIECES[] = {'p', 's', 'g', 'w', 'h', 'k'};
const int PIECE_MOVE_DISTANCE[] = {2, 1, -1, -1, -1, 1};
const int SCORES[] = {1, 3, 4, 5, 9, WIN_SCORE};
#define MAX_MOVES 8
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

const int get_piece_score(char piece) {
    return SCORES[get_piece_index(piece)];
}

int **get_piece_moves(char piece) {
    const int i = get_piece_index(piece);
    int **moves = malloc(MAX_MOVES * sizeof(int *));
    for (int x = 0; x < MAX_MOVES; x++) {
        moves[x] = malloc(2 * sizeof(int));
        if (MOVES[i][x][0] == 0 && MOVES[i][x][1] == 0) {
            moves[x] = 0;
        } else {
            moves[x][0] = MOVES[i][x][0];
            moves[x][1] = MOVES[i][x][1];
        }
    }
    return moves;
}

int get_board_score(char board[BOARD_WIDTH][BOARD_HEIGHT]) {
    int score = 0;
    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_HEIGHT; y++) {
            score += get_piece_score(board[x][y]);
        }
    }
    return score;
}

void clear_board(char board[BOARD_WIDTH][BOARD_HEIGHT]) {
    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_HEIGHT; y++) {
            board[x][y] = ' ';
        }
    }
}

void print_board(char board[BOARD_WIDTH][BOARD_HEIGHT]) {
    for (int i = 0; i < BOARD_WIDTH; ++i) {
        printf("%d", i + 1);
    }
    printf("\n");
    for (int y = 0; y < BOARD_WIDTH; y++) {
        for (int x = 0; x < BOARD_HEIGHT; x++) {
            printf("%c", board[x][y]);
        }
        printf("\n");
    }
}


int main() {
//    int** moves = get_piece_moves('p');
//    for (int i = 0; moves[i]; i++) {
//        printf("%d %d\n", moves[i][0], moves[i][1]);
//    }
    char board[BOARD_HEIGHT][BOARD_WIDTH];
    clear_board(board);
    print_board(board);
}