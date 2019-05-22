/*********************************************************
 *  agent.c
 *  Nine-Board Tic-Tac-Toe Agent
 *  COMP3411/9414/9814 Artificial Intelligence
 *  Alan Blair, CSE, UNSW
 */
#define MAX_MOVE 81
#define INF 9999999
#define TRUE 1
#define FALSE 0
#define WIN_SCORE 100
#define LOSS_SCORE (-100)
#define DRAW_SCORE 0

int board[10][10];
int move[MAX_MOVE + 1];
int player;
int m;

extern int port;
extern char *host;

//  parse command-line arguments
void agent_parse_args(int argc, char *argv[]);

//  called at the beginning of a series of games
void agent_init();

//  called at the beginning of each game
void agent_start(int this_player);

int agent_second_move(int board_num, int prev_move);

int agent_third_move(int board_num, int first_move, int prev_move);

int agent_next_move(int prev_move);

void agent_last_move(int prev_move);

//  called at the end of each game
void agent_gameover(int result, int cause);

//  called at the end of the series of games
void agent_cleanup();

int evaluate(int board_num);

int minimax(int a, int b, int depth);
