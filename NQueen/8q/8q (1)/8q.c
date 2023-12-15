#include "8q.h"

int main(int argc, char* argv[])
{

if (argc < 2)
{
    fprintf(stderr, "Usage: expected number of arguements is atleast 2\n");
    exit(EXIT_FAILURE);
}

bool verbose = false;
int boardsize = 0; 
for (int i = 0; i < argc; i++)
{
    if (strcmp(argv[i], "-verbose") == 0)
    {
        verbose = true;
    }
    else
    {
        boardsize = atoi(argv[i]);
    }

}
test();
if (boardsize <= 0 || boardsize > MAX)
{
    fprintf(stderr, "invalid board size. It must be between 1 and %d\n", MAX);
    exit(EXIT_FAILURE);
}

if (boardsize == 2 || boardsize == 3)
{
    fprintf(stderr, "No solutions for this board size.\n");
    exit(EXIT_FAILURE);
}

int nq_solutions = solution(boardsize, verbose);
printf("%d solution(s)\n", nq_solutions);
    
    return 0;
}

void makeboard(Board *cb, int boardsize)

{
    for (int row = 0; row < boardsize; row++)
    {
        for (int col = 0; col < boardsize; col++)
        {
            cb->grid[row][col] = EMPTY;
        }
    }
}

void board2string(char str[MAX * MAX + 1], Board *cb)
{
    int count = 0; 

    for (int row = 0; row < MAX; row++)
    {
        for (int col = 0; col < MAX; col++)
        {
            if (cb->grid[row][col] == QUEEN || cb->grid[row][col] == EMPTY)
            {
                str[count] = cb->grid[row][col];
                count++;
            }
        }
    }
    str[count] = '\0';
}

bool isSafe(Board *cb, int row, int col, int boardsize)
{
for (int i = 0; i < boardsize; i++)
{
    if (cb->grid[row][i] == QUEEN || cb->grid[i][col] == QUEEN)
    {
        return false;
    }
}

for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
{
    if (cb->grid[i][j] == QUEEN)
    {
        return false;
    }
}

for (int i = row, j = col; i < boardsize && j < boardsize; i++, j++)
{
    if (cb->grid[i][j] == QUEEN)
    {
        return false;
    }
}

for (int i = row, j = col; i >= 0 && j < boardsize; i--, j++)
{
    if (cb->grid[i][j] == QUEEN)
    {
        return false;
    }
}

for (int i = row, j = col; i < boardsize && j >= 0; i++, j--)
{
    if (cb->grid[i][j] == QUEEN)
    {
        return false;
    }
}

return true;
}

bool isSolution(Board *cb, int boardsize) 
{
int queens_count = 0;
for (int i = 0; i < boardsize; i++)
{
    for (int j = 0; j < boardsize; j++)
    {
        if (cb->grid[i][j] == QUEEN)
        queens_count++;
    }
}

if (!(queens_count == boardsize))
{
    return false;
}
return true;
}

bool placequeen(Board *cb, int row, int col, int boardsize)
{
if (isSafe(cb, row, col, boardsize))
{
    cb->grid[row][col] = QUEEN;
    return true;
}
return false;
}

bool isUnique(Board *new_board, Board board_list[], int first, int last, int boardsize)
{
for (int i = first; i < last; i++)
{
    bool same_board = true;
    for (int row = 0; row < boardsize && same_board; row++) 
    {
        for (int col = 0; col < boardsize && same_board; col++)
        {
            if (new_board->grid[row][col] != board_list[i].grid[row][col])
            same_board = false;
        }
    }
    if (same_board == true)
    {
        return false;
    }
}
return true;
}

int new_row(Board *cb, int boardsize) 
{

    for (int row = 0; row < boardsize; row++) 
    {
        bool rowHasQueen = false;
        for (int col = 0; col < boardsize; col++) 
        {
            if (cb->grid[row][col] == QUEEN) 
            {
                rowHasQueen = true;
                
            }
        }

        if (!rowHasQueen)
        {
            return row;
        }
        
    }
    return boardsize; // All rows have queens, should not happen in the BFS context
}

int solution(int boardsize, bool verbose) 
{

Board board_list[MAX_LIST];

int first = 0; 
int last = 0;
int solutions_count = 0;


makeboard(&board_list[last], boardsize);
last++;

while (first < last) 
{
    Board current_board = board_list[first];
    first++;

    if (isSolution(&current_board, boardsize))
    {
        solutions_count++;
        if (verbose == true)
        {
            printVerbose(&current_board, boardsize);
        }
    }

    else
        {
            int next_row = new_row(&current_board, boardsize);

            for (int col = 0; col < boardsize; col++)
            {
                Board new_board = current_board;
                if (placequeen(&new_board, next_row, col, boardsize))
                {
                    if (isUnique(&new_board, board_list, first, last, boardsize))
                    {
                        board_list[last] = new_board;
                        last++;
                    }
                }
            }
        }
    }
  return solutions_count;
}

void printVerbose(Board *cb, int boardsize)

{
    for (int i = 0; i < boardsize; i++)
    {
        for (int j = 0; j < boardsize; j++)

        if (cb->grid[i][j] == QUEEN)
        {
            printf("%d", j + 1);
        }
    }
    printf("\n");
}

void test(void)
{

// test makeboard 
    Board t;
    char s[1000];
    makeboard(&t, 5);
    board2string(s, &t);
    assert(strcmp(s, ".........................") == 0);

    placequeen(&t, 0, 0, 5);
    assert (isSafe(&t, 0, 3, 5) == false);
    assert (isSafe(&t, 4, 0, 5) == false);
    assert (isSafe(&t, 1, 1, 5) == false);

    Board q;
    makeboard(&q, 5);
    placequeen(&q, 4, 4, 5);
    assert (isSafe(&q, 2, 2, 5) == false);

    Board i;
    char m[1000];
    makeboard(&i, 10);
    board2string(m, &i);
    assert(strcmp(m, "....................................................................................................") == 0);

    placequeen(&i, 0, 0, 5);
    assert (isSafe(&i, 0, 3, 10) == false);
    assert (isSafe(&i, 4, 0, 10) == false);
    assert (isSafe(&i, 1, 1, 10) == false);

    Board j;
    makeboard(&j, 10);
    placequeen(&j, 4, 4, 10);
    assert (isSafe(&j, 2, 2, 10) == false);

    Board a, b, c;

    makeboard(&a, 3);
    makeboard(&b, 3);
    makeboard(&c, 3);

    placequeen(&a, 1, 2, 3);
    placequeen(&a, 0, 0, 3);
    placequeen(&a, 1, 2, 3);

    Board board_list[10000];
    board_list[0] = a;
    board_list[1] = b;
    board_list[2] = c;

    assert (isUnique(&c, board_list, 0, 2, 3) == false);

    Board d;
    makeboard(&d, 4);
    placequeen(&d, 0, 2, 4);
    placequeen(&d, 1, 0, 4);
    placequeen(&d, 2, 3, 4);
    assert (new_row(&d, 4) == 3);


 bool verbose = false;

    assert (solution(1, verbose) == 1);
    assert (solution(4, verbose) == 2);
    assert (solution(5, verbose) == 10);
    assert (solution(6, verbose) == 4);
    assert (solution(7, verbose) == 40);
    assert (solution(8, verbose) == 92);
    assert (solution(9, verbose) == 352);
}
