/*********************************************************
 *  agent.c
 *  Nine-Board Tic-Tac-Toe Agent
 *  COMP3411/9414/9814 Artificial Intelligence
 *  Alan Blair, CSE, UNSW
 *
 *  The main function of the program is the `minimax`, which is used to get the current best action (namely
 *  the action with the highest state evaluation value) every time it is the agent's turn to take action.Search
 *  algorithm combined with alpha-beta pruning algorithm and a heuristic function `evaluate`.
 *
 *  This function evaluates the score of the current sub-board to a linear evaluation function,
 *  and the specific formula is defined as Eval(s) = 3 * X_2(s) + X_1(s) - (3 * O_2(s) + O_1(s)). The `X_n` is
 *  defined as the number of rows, columns or diagonals with exactly n X's and no O's. Similarly, `O_n` is the
 *  number of rows, columns or diagonals with just n O's.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>

#include "common.h"
#include "agent.h"
#include "game.h"

#define MAX_DEPTH 11

int best_move;


// Enumerate all possible status in a sub-board that could win
int win_status[8][3] = {
        {1, 4, 7},
        {2, 5, 8},
        {3, 6, 9},
        {1, 5, 9},
        {3, 5, 7},
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};


int _max(int a, int b) {
    return a > b ? a : b;
}


// The minimax algorithm with alpha-beta pruning and heuristics
int minimax(int a, int b, int depth) {
    if (depth == 0) // If proceed the MAX_DEPTH
        return evaluate(move[m]); // return the evaluation of current state

    int best_value = -INF;
    int value = 0;

    for (int next_move = 1; next_move < 10; ++next_move) {
        if (board[move[m]][next_move] != EMPTY) continue;

        move[++m] = next_move; // Try the next move
        int cur_player;
        if ((MAX_DEPTH - depth) % 2 == 0) cur_player = player;
        else cur_player = !player;

        int state = make_move(cur_player, m, move, board);

        if (state == STILL_PLAYING) value = -minimax(-b, -a, depth - 1);
        else if (state == DRAW) value = DRAW_SCORE;
        else if (state == LOSS) value = LOSS_SCORE;
        else if (state == WIN) value = WIN_SCORE;

        if (value > best_value) {
            best_value = value;
            if (depth == MAX_DEPTH) best_move = next_move; // Only update best_move on the top level
        }

        a = _max(value, a);

        board[move[m - 1]][move[m]] = EMPTY; // reset
        m--;

        // Pruning
        if (a >= b) break;
    }

    return best_value;
}


// Evaluate a single 9-slot board given a board number
int evaluate(int board_num) {
    // Define Xn as the number of rows, columns or diagonals with exactly n X's and no O's.
    // Similarly, On is the number of rows, columns or diagonals with just n O's.
    int X2 = 0, O2 = 0;
    int X1 = 0, O1 = 0;

    // Compute X2, X1, O2, O1
    for (int i = 0; i < 8; ++i) {
        if (((board[board_num][win_status[i][0]] == EMPTY) &&
             (board[board_num][win_status[i][1]] == player) &&
             (board[board_num][win_status[i][2]] == player)) ||
            ((board[board_num][win_status[i][0]] == player) &&
             (board[board_num][win_status[i][1]] == EMPTY) &&
             (board[board_num][win_status[i][2]] == player)) ||
            ((board[board_num][win_status[i][0]] == player) &&
             (board[board_num][win_status[i][1]] == player) &&
             (board[board_num][win_status[i][2]] == EMPTY))) {
            X2++;
        } else if (((board[board_num][win_status[i][0]] == EMPTY) &&
                    (board[board_num][win_status[i][1]] == !player) &&
                    (board[board_num][win_status[i][2]] == !player)) ||
                   ((board[board_num][win_status[i][0]] == !player) &&
                    (board[board_num][win_status[i][1]] == EMPTY) &&
                    (board[board_num][win_status[i][2]] == !player)) ||
                   ((board[board_num][win_status[i][0]] == !player) &&
                    (board[board_num][win_status[i][1]] == !player) &&
                    (board[board_num][win_status[i][2]] == EMPTY))) {
            O2++;
        } else if (((board[board_num][win_status[i][0]] == player) &&
                    (board[board_num][win_status[i][1]] == EMPTY) &&
                    (board[board_num][win_status[i][2]] == EMPTY)) ||
                   ((board[board_num][win_status[i][0]] == EMPTY) &&
                    (board[board_num][win_status[i][1]] == player) &&
                    (board[board_num][win_status[i][2]] == EMPTY)) ||
                   ((board[board_num][win_status[i][0]] == EMPTY) &&
                    (board[board_num][win_status[i][1]] == EMPTY) &&
                    (board[board_num][win_status[i][2]] == player))) {
            X1++;
        } else if (((board[board_num][win_status[i][0]] == !player) &&
                    (board[board_num][win_status[i][1]] == EMPTY) &&
                    (board[board_num][win_status[i][2]] == EMPTY)) ||
                   ((board[board_num][win_status[i][0]] == EMPTY) &&
                    (board[board_num][win_status[i][1]] == !player) &&
                    (board[board_num][win_status[i][2]] == EMPTY)) ||
                   ((board[board_num][win_status[i][0]] == EMPTY) &&
                    (board[board_num][win_status[i][1]] == EMPTY) &&
                    (board[board_num][win_status[i][2]] == !player))) {
            O1++;
        }

    }

    // Return the evaluated score of this board
    return 3 * (X2 - O2) + (X1 - O1);
}


/*********************************************************//*
   Print usage information and exit
*/
void usage(char argv0[]) {
    printf("Usage: %s\n", argv0);
    printf("       [-p port]\n"); // tcp port
    printf("       [-h host]\n"); // tcp host
    exit(1);
}

/*********************************************************//*
   Parse command-line arguments
*/
void agent_parse_args(int argc, char *argv[]) {
    int i = 1;
    while (i < argc) {
        if (strcmp(argv[i], "-p") == 0) {
            if (i + 1 >= argc) {
                usage(argv[0]);
            }
            port = atoi(argv[i + 1]);
            i += 2;
        } else if (strcmp(argv[i], "-h") == 0) {
            if (i + 1 >= argc) {
                usage(argv[0]);
            }
            host = argv[i + 1];
            i += 2;
        } else {
            usage(argv[0]);
        }
    }
}

/*********************************************************//*
   Called at the beginning of a series of games
*/
void agent_init() {
    struct timeval tp;

    // generate a new random seed each time
    gettimeofday(&tp, NULL);
    srandom((unsigned int) (tp.tv_usec));
}

/*********************************************************//*
   Called at the beginning of each game
*/
void agent_start(int this_player) {
    reset_board(board);
    m = 0;
    move[m] = 0;
    player = this_player;
}

/*********************************************************//*
   Choose second move and return it
*/
int agent_second_move(int board_num, int prev_move) {
    int this_move;
    move[0] = board_num;
    move[1] = prev_move;
    board[board_num][prev_move] = !player;

    best_move = -INF;
    minimax(-INF, INF, MAX_DEPTH);
    this_move = best_move;

//    printf("%d\n", this_move);

    move[++m] = this_move;
    board[prev_move][this_move] = player;

    return (this_move);
}

/*********************************************************//*
   Choose third move and return it
*/
int agent_third_move(
        int board_num,
        int first_move,
        int prev_move
) {
    int this_move;
    m = 0;
    move[m++] = board_num;
    move[m++] = first_move;
    move[m] = prev_move;
    board[board_num][first_move] = player;
    board[first_move][prev_move] = !player;

    best_move = -INF;
    minimax(-INF, INF, MAX_DEPTH);
    this_move = best_move;

//    printf("%d\n", this_move);

    move[++m] = this_move;
    board[prev_move][this_move] = player;
    return (this_move);
}

/*********************************************************//*
   Choose next move and return it
*/
int agent_next_move(int prev_move) {
    int this_move;
    m++;
    move[m] = prev_move;
    board[move[m - 1]][move[m]] = !player;

    best_move = -INF;
    minimax(-INF, INF, MAX_DEPTH);
    this_move = best_move;

//    printf("%d\n", this_move);

    move[++m] = this_move;
    board[prev_move][this_move] = player;
    return (this_move);
}

/*********************************************************//*
   Receive last move and mark it on the board
*/
void agent_last_move(int prev_move) {
    m++;
    move[m] = prev_move;
    board[move[m - 1]][move[m]] = !player;
}

/*********************************************************//*
   Called after each game
*/
void agent_gameover(
        int result,// WIN, LOSS or DRAW
        int cause  // TRIPLE, ILLEGAL_MOVE, TIMEOUT or FULL_BOARD
) {
    // nothing to do here
}

/*********************************************************//*
   Called after the series of games
*/
void agent_cleanup() {
    // nothing to do here
}
