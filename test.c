#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define ROW 8
#define COL 7
#define NUMBOARDS 300000000
#define JUMP_UP 1
#define JUMP_LEFT 2
#define JUMP_RIGHT 3
#define SUCCESS 0
#define HEAD -1
#define NONE 0
#define TILE '*'
#define EMPTY '.'


typedef struct sold_board
{
	char board[ROW][COL];
	int parentIndex;

} sold_board;


int possibility(int parentIndex, int nextIndex, sold_board *boardList, int targetRow, int targetCol);
int checkMoves(sold_board *boardList, int r, int c, int parentIndex);
bool checkSuccess(int r, int c, int targetRow, int targetCol);
void printPath(int nextIndex, sold_board *boardList);
int addNewBoardToList(sold_board *boardList, int parentIndex, int nextIndex, int r, int c, int move);
void initialize(char board[ROW][COL]);
void print(char board[ROW][COL]);
void copy(char from[ROW][COL], char to[ROW][COL]);
char safe(char board[ROW][COL], int r, int c);
void testing(void);

void testing(void)
{
	sold_board test[5];

	int i, j;

	test[0].parentIndex = 0;

/*	test[0].board = {
			 {'.', '.', '.', '.', '.', '.', '.'},
			 {'.', '.', '.', '.', '.', '.', '.'},
			 {'.', '.', '.', '.', '.', '.', '.'},
			 {'.', '*', '*', '*', '.', '.', '.'},
			 {'*', '.', '.', '.', '*', '*', '.'},
			 {'*', '.', '.', '.', '.', '.', '.'},
			 {'.', '.', '.', '.', '.', '.', '.'},
			 {'.', '.', '.', '.', '.', '.', '.'}}; */

	for(i = 0; i < ROW; i++) {
		for(j = 0; j < COL; j++) {
			test[0].board[i][j] = EMPTY;
		}
	}
	test[0].board[3][1] = TILE;
	test[0].board[3][2] = TILE;
	test[0].board[3][3] = TILE;
	test[0].board[4][0] = TILE;
	test[0].board[5][0] = TILE;
	test[0].board[4][4] = TILE;
	test[0].board[4][5] = TILE;

	assert(checkMoves(test, 3, 0, 0) == JUMP_UP);
	assert(checkMoves(test, 3, 4, 0) == JUMP_RIGHT);
	assert(checkMoves(test, 4, 3, 0) == JUMP_LEFT);
	assert(checkSuccess(3, 0, 3, 3) == false);
	assert(checkSuccess(3, 3, 3, 3) == true);
	assert(addNewBoardToList(test, 0, 1, 3, 0, JUMP_UP) == 2);
	assert(possibility(0, 1, test, 2, 1) == 5);
	assert(safe(test[0].board, -1, 0) == '0');
	assert(safe(test[0].board, 0, 0) == EMPTY);
}
