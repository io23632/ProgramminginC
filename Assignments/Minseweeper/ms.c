#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAXSQ 10

typedef struct board {
   int grid[MAXSQ][MAXSQ];
   int w;
   int h;
   int totmines;
} board;

#define UNK  '?'
#define MINE 'X'


board apply_rule1(board b);
int minecount(board b);
board apply_rule_2(board b);

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

bool changes_made = true;

while (changes_made){
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
                        if (ni >= 0 && ni < b.h && nj >= 0 && nj < b.w && b.grid[ni][nj] == MINE)
                        {
                            count++;
                            changes_made = true;
                        }
                    }
                } 
                  b.grid[i][j] = count;
            }
        }
    }
}

}
return b; 
}

board apply_rule_2(board b)
{
bool changes_made = true;

while (changes_made) 
{
    changes_made = false;

    for (int i = 0; i < b.h; i++)
    {
        for (int j = 0; j < b.w; j++)
        {
            if (b.grid[i][j] >= 0 && b.grid[i][j] <= 8)
            {
                int n = b.grid[i][j];
                int m = 0;
                int u = 0;

                for (int ni = i - 1; ni < i + 2; ni++)
                {
                    for (int nj = j - 1; nj < j + 2; nj++)
                    {
                    
                    if (ni >= 0 && ni < b.h && nj >= 0 && nj < b.w)
                    {
                        // Check if the surrounding is a mine, add to m:
                       if (b.grid[ni][nj] == MINE)
                       {
                           m++;
                       }
                       // or if it is a unknown, add to u counter:
                       else if (b.grid[ni][nj] == UNK)
                       {
                           u++;
                       }
                    }

                    }

                }
                // if n = m + u, then mark all unknowns as mines:
                if (n == m + u)
                {
                    for (int ni = i - 1; ni < i + 2; ni++)
                    {
                        for (int nj = j - 1; nj < j + 2; nj++)
                        {
                            if (ni >= 0 && ni < b.h && nj >= 0 && nj < b.w && b.grid[ni][nj] == UNK)
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
}
return b; 
}

board solve_board(board b)
{
bool changed;

    do {
        changed = false;
        board newBoard = apply_rule1(b);
        b = newBoard;
        
        newBoard = apply_rule_2(b);
        b = newBoard;

    } while (changed); // keep applying rules until no more changes are made

    return b;
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

        else if (b.grid[i][j] == MINE)
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

bool syntax_check(unsigned totmines, unsigned width, unsigned height, char inp[MAXSQ*MAXSQ+1])
{  
// Make sure number of characters in string == width*height
unsigned expectedLength = width * height;
int string_length = strlen(inp);

if (expectedLength != string_length)
{
    return false;
}

// Ensure only characters are from the set:   012345678?X

for (unsigned i = 0; i < expectedLength; i++)
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
            return false;
        }
    }

// Ensure mines in string <= totmines

//Count the numebr of mines in the string 
int minecount = 0;
for (unsigned i = 0; i < expectedLength; i++)
{
    if (inp[i] == 'X')
    {
        minecount++;
    }
}

if (minecount > totmines)
{
    return false;
}
//if all check pass:
return true;

}

board make_board(int totmines, int width, int height, char inp[MAXSQ*MAXSQ+1])
{
    board b; 

    b.w = width;
    b.h = height;
    b.totmines = totmines;

    int count = 0; 

    // Initialise the board: 
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Check if the string has the characters 0 - 8 or are MINE AND UNK
            if (inp[count] >= '0' && inp[count] <= '8')
            {
                b.grid[i][j] = inp[count] - '0';
            }
            else if (inp[count] == MINE || inp[count] == UNK )
            {
                b.grid[i][j] = inp[count];
            }

            count++;
        }
    }
    return b;
}

void test(void)
{
}