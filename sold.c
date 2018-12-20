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

int main(int argc, char *argv[])
{
	static sold_board boardList[NUMBOARDS];

	int targetCol;
	int targetRow;

	int parentIndex = 0;
	int nextIndex = 1;
	int lastIndex = 1;
	bool isPossible = true;

	testing();

	/* target */
	if(argc != 3) {
		printf("Please enter the correct value.\n");
		exit(0);
	}
	else {
		sscanf(argv[1], "%d", &targetCol);
		sscanf(argv[2], "%d", &targetRow);
		if(targetCol >= COL || targetCol < 0 || targetRow >= ROW/2 || targetRow < 0) {
			printf("Please enter the correct value.\n");
			exit(0);
		}
	}

	printf("\nTarget = (%d, %d)\n", targetCol, targetRow);
	printf("-----------------------------\n");

	/* soldier board */
	initialize(boardList[0].board);
	boardList[0].parentIndex = -1;

	while(isPossible) {
		nextIndex = possibility(parentIndex, nextIndex, boardList, targetRow, targetCol);

		if(nextIndex > NUMBOARDS) {
			printf("!! Sorry, Out of Memory !!\n");
			isPossible = false;
		}
		else {
			if(nextIndex > lastIndex) {
				lastIndex = nextIndex;
			}
			else {
				if(nextIndex == SUCCESS) {
					isPossible = false;
				}
				if(nextIndex == lastIndex) {
					printf("!! Unachievable !!\n");
					isPossible = false;
				}
			}
		}

		parentIndex++;
	}

	return 0;
}

int possibility(int parentIndex, int nextIndex, sold_board *boardList, int targetRow, int targetCol)
{
	int i, j, move;

	for(i = 0; i < ROW; i++) {
		for(j = 0; j < COL; j++) {
			move = checkMoves(boardList, i, j, parentIndex);
			if(move != NONE) {
				nextIndex = addNewBoardToList(boardList, parentIndex, nextIndex, i, j, move);

				if(checkSuccess(i, j, targetRow, targetCol)){
					printPath(nextIndex, boardList);
					return SUCCESS;
				}
			}
		}
	}

	return nextIndex;
}

int checkMoves(sold_board *boardList, int r, int c, int parentIndex)
{
	if(safe(boardList[parentIndex].board, r, c) == EMPTY) {
		if(safe(boardList[parentIndex].board, r+1, c) == TILE && safe(boardList[parentIndex].board, r+2, c) == TILE) {
			return JUMP_UP;
		}
		if(safe(boardList[parentIndex].board, r, c+1) == TILE && safe(boardList[parentIndex].board, r, c+2) == TILE) {
			return JUMP_LEFT;
		}
		if(safe(boardList[parentIndex].board, r, c-1) == TILE && safe(boardList[parentIndex].board, r, c-2) == TILE) {
			return JUMP_RIGHT;
		}
	}

	return NONE;
}

bool checkSuccess(int r, int c, int targetRow, int targetCol)
{
	if(r == targetRow && c == targetCol) {
		return true;
	}
	return false;
}

void printPath(int nextIndex, sold_board *boardList)
{
	int currentIndex = nextIndex - 1;

	while(currentIndex != HEAD) {
		printf("Current Index: %d\n", currentIndex);
		printf("Parent Index: %d\n", boardList[currentIndex].parentIndex);
		print(boardList[currentIndex].board);
		printf("-----------------------------\n");

		/* trace back: set currentIndex to the current board's parent index */
		currentIndex = boardList[currentIndex].parentIndex;
	}

	printf("!! Success !!\n");

}

int addNewBoardToList(sold_board *boardList, int parentIndex, int nextIndex, int r, int c, int move)
{
	copy(boardList[parentIndex].board, boardList[nextIndex].board);

	if(move == JUMP_UP) {
		boardList[nextIndex].board[r][c] = TILE;
		boardList[nextIndex].board[r+1][c] = EMPTY;
		boardList[nextIndex].board[r+2][c] = EMPTY;
	}
	if(move == JUMP_LEFT) {
		boardList[nextIndex].board[r][c] = TILE;
		boardList[nextIndex].board[r][c+1] = EMPTY;
		boardList[nextIndex].board[r][c+2] = EMPTY;
	}
	if(move == JUMP_RIGHT) {
		boardList[nextIndex].board[r][c] = TILE;
		boardList[nextIndex].board[r][c-1] = EMPTY;
		boardList[nextIndex].board[r][c-2] = EMPTY;
	}

	boardList[nextIndex].parentIndex = parentIndex;

	nextIndex += 1;

	return nextIndex;
}

void initialize(char board[ROW][COL])
{
	int i, j;

	for(i = 0; i < ROW; i++) {
		for(j = 0; j < COL; j++) {
			if(i < ROW/2) {
				board[i][j] = EMPTY;
			}
			else {
				board[i][j] = TILE;
			}
		}
	}
}

void print(char board[ROW][COL])
{
	int i, j;

	for(i = 0; i < ROW; i++) {
		for(j = 0; j < COL; j++) {
			printf("%c", board[i][j]);
		}
		printf("\n");
	}
}

void copy(char from[ROW][COL], char to[ROW][COL])
{
	int i, j;

	for(i = 0; i < ROW; i++) {
		for(j = 0; j < COL; j++) {
			to[i][j] = from[i][j];
		}
	}
}

char safe(char board[ROW][COL], int r, int c)
{
	if(r < 0 || c < 0 || r >= ROW || c >= COL) {
		return '0';
	}
	return board[r][c];
}
