// Change the INSLST from if else to switch cases:


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

#define MAXTOKENSIZE 10000

/*

GRAMMAR to parse:

<PROG> ::= "START" <INSLST>
<INSLST> ::= "END" | <INS> <INSLST>
<INS> ::= <FWD> | <RGT> | <COL>
<FWD> ::= "FORWARD" <VARNUM>
<RGT> ::= "RIGHT" <VARNUM>
<COL> ::= "COLOUR" <VAR> | "COLOUR" <WORD>
<VARNUM> ::= <VAR> | <NUM>
<VAR> ::= $<LTR>
<LTR> ::= A, B, ....... Z
<NUM> ::= 10 or -17.99 etc.
<WORD> ::= "RED", "BLUE" , "HELLO!" or "178"
<OP> ::= "+" | "-" | "*" | "/" 

*/

typedef enum{
    INS_FWD,
    INS_RGT,
    INS_COL,
}INSTYPE;

typedef enum{
    PLUS,
    MINUS,
    DIVIDE,
    MULT,
}OP;

typedef double NUM;
typedef char LTR;


typedef struct PROG{
    char input[MAXTOKENSIZE][MAXTOKENSIZE];
    int current_count;
}prog;

typedef struct RGT{
    INSTYPE type;
    union {
        LTR variable;
        NUM number;
    }RGT_postfix;
}RGT;

typedef struct WORD
{
    const char* str;
}WORD;

typedef struct Operation{
    
}Op;

typedef struct COL{
    INSTYPE type;
    union {
        LTR variable;
        WORD word;
    }COL_postfix;
}COL;

typedef struct FWD{
    INSTYPE type;
    union {
        LTR variable;
        NUM number;
    }FWD_postfix;
}FWD;



void parseINSLST(prog* p){

char input[MAXTOKENSIZE] = p->input[p->current_count];

switch (input)
{
case "END":
    /* code */
    break;

default:
    break;
}


}
