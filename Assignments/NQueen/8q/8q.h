#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#define MAX 10
#define MAX_LIST 10000
#define QUEEN 'Q'
#define EMPTY '.'

typedef struct {
    char grid[MAX][MAX];
} Board;

void makeboard(Board *cb, int boardsize);
void board2string(char str[MAX * MAX + 1], Board *cb);
bool isSafe(Board *cb, int row, int col, int boardsize);
bool placequeen(Board *cb, int row, int col, int boardsize);
bool isUnique(Board *new_board, Board board_list[], int row, int col, int boardsize);
bool isSolution(Board *cb, int boardsize);
int new_row(Board *cb, int boardsize);
int solution(int boardsize, bool verbose);
void printVerbose(Board *cb, int boardsize);
void test(void);
