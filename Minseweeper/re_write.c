#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAXSQ 10
#define UNK  '?'
#define MINE 'X'

typedef struct board {
    int grid[MAXSQ][MAXSQ];
    int w;
    int h;
    int totmines;
} board;



board make_board(int totmines, int width, int height, char inp[MAXSQ*MAXSQ+1]);
bool syntax_check(unsigned totmines, unsigned width, unsigned height, char inp[MAXSQ*MAXSQ+1]);
void board2str(char s[MAXSQ*MAXSQ+1], board b);
int minecount(board b);
board apply_rule1(board b);
board apply_rule_2(board b);
board solve_board(board b);

int main(void)

{
    return 0;

}




int minecount(board b)
{
    int mine_count = 0;

    for (int i = 0; i < b.h; i++)
    {
        for (int j = 0; j < b.w; j++)
        {
            if (b.grid[i][j] == MINE)
            {
                mine_count++;
            }
        }
    }

    return mine_count;
}

board apply_rule1(board b)
{
    static int loop_counter = 0;
    bool changes_made = true;

    while (changes_made)
    {
        changes_made = false;

        int mines_found = minecount(b);

        if (mines_found == b.totmines)
        {
            for (int i = 0; i < b.h; i++)
            {
                for (int j = 0; j < b.w; j++)
                {
                    if (b.grid[i][j] == UNK)

                    {
                        int count = 0;
                        for (int ni = i - 1; ni < i + 2; ni++)
                        {
                            for (int nj = j - 1; nj < j + 2; nj++)
                            {
                                if (ni >= 0 && ni < b.h && nj >= 0 && nj < b.w)
                                {
                                    if (b.grid[ni][nj] == MINE)
                                    {
                                        count++;
                                        changes_made = true;
                                    }

                                }
                            }
                        }
                        b.grid[i][j] = count;
                    }
                }
            }
        }
        loop_counter++;
    }

    return b;
}

board apply_rule_2(board b)
{
    static int loop_counter = 0;
    bool changes_made = true;

    while (changes_made)
    {
        changes_made = false;

        for (int i = 0; i < b.h; i++) {
            for (int j = 0; j < b.w; j++) {
                int n = b.grid[i][j];
                int m = 0;
                int u = 0;

                for (int ni = i - 1; ni < i + 2; ni++) {
                    for (int nj = nj - 1; nj < j + 2; nj++) {
                        if (ni >= 0 && ni < b.h && nj >= 0 && nj < b.w) {
                            if (b.grid[ni][nj] == MINE) {
                                m++;
                            } else if (b.grid[ni][nj] == UNK) {
                                u++;
                            }

                        }
                    }
                }
                // if n = m + u, then mark all unknowns as mines:
                if (n == m + u) {
                    for (int ni = i - 1; ni < i + 2; ni++)
                    {
                        for (int nj = j - 1; nj < j + 2; nj++)
                        {
                            if (ni >= 0 && ni < b.h && nj >= 0 && nj < b.w)
                            {
                                if (b.grid[ni][nj] == UNK)
                                {
                                    b.grid[ni][nj] = MINE;
                                    changes_made = true;
                                }
                            }


                        }

                    }
                }
            }

        }

        loop_counter++;
    }

    return b;
}

board solve_board(board b)

{
bool changed = true;
while (changed)
{
changed = false;
board solved_board = apply_rule1(b);
b = solved_board;

solved_board = apply_rule_2(b);
b = solved_board;
}
    return b;
}

board make_board(int totmines, int width, int height, char inp[MAXSQ*MAXSQ+1])
{
    int count = 0;
    board b;
    b.totmines = totmines;
    b.w = width;
    b.h = height;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            if (inp[count] >= '0' && inp[count] <= '8')
            {
                b.grid[i][j] = inp[count] - '0';
            }
            else if (inp[count] == MINE)
            {
                b.grid[i][j] = MINE;
            }
            else
            {
                b.grid[i][j] = UNK;
            }

            count++;
        }
    }
    return b;
}

bool syntax_check(unsigned totmines, unsigned width, unsigned height, char inp[MAXSQ*MAXSQ+1])
{

    // Check if expected length is the same as the input string
    unsigned expected_length = width * height;
    unsigned input_length = strlen(inp);
    if (expected_length != input_length)
    {
        printf("length of string does not equal width * height");
        return false;
    }

    // ENsure characters from the input only contain characters from : 0123456789X?

    for (unsigned i = 0; i < expected_length; i++)
    {
        char c = inp[i];
        switch (c)
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case 'X':
            case '?':
                break;
            default:
                printf("Invalid Characters\n");
                return false;
        }

    }

    // Check the total number of mine; totmines is equal to mine count

    unsigned mine_count= 0;

    for (unsigned i = 0; i < expected_length; i++)
    {
        if (inp[i] == MINE)
        {
            mine_count++;
        }
    }

    if (mine_count > totmines)
    {
        printf("Minecount is greater than the totalmines\n");
        return false;
    }

    return true;
}

void board2str(char s[MAXSQ*MAXSQ+1], board b)
{
    int count = 0;

    for (int i = 0; i < b.h; i++)
    {
        for (int j = 0; j < b.w; j++)
        {
            if (b.grid[i][j] >= 0 && b.grid[i][j] <= 8)
            {
                s[count] = '0' + b.grid[i][j];
            }
            else if (b.grid[i][j] = MINE)
            {
                s[count] = MINE;
            }
            else
            {
                s[count] = UNK;
            }
            count++;
        }
    }
    s[count] = '\0';
}