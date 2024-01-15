#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

#define MAXTOKENSIZE 1000

typedef enum{
    INS_FWD,
    INS_RGT,
}INSTYPE;

typedef double NUM;

typedef struct PROG{
    char input[MAXTOKENSIZE][MAXTOKENSIZE];
    int current_count;
}prog;


typedef struct RGT{
    INSTYPE type;
    NUM number;
}RGT;


typedef struct FWD{
    INSTYPE type;
    NUM number;
}FWD;


typedef struct TurtleState {
    int x;
    int y;
    int direction;
}Ts;



void parsePROG(prog* p, Ts* turtle);
void parseINSLST(prog* p, Ts* turtle);
bool isNUMBER(const char* str);
FWD parseFWD(prog* p, Ts* turtle);
void move_fwd(Ts* turtle, NUM distance);
RGT parseRGT(prog* p, Ts* turtle);
void move_rgt(Ts* turtle, int angle);
void print_W(int n);