#include <stdio.h>
#include <stdlib.h>

#define MAXTOKENSIZE 20
/*
<PROG> ::= "START" <INSLST>
<INSLST> ::= "END" | <INS> <INSLST>
<INS> ::= <FWD> | <RGT>
<FWD> ::= "FORWARD" <NUM>
<RGT> ::= "RIGHT" <NUM>
<NUM> ::= 10 or -17.99 etc.
*/

typedef enum INSTYPE{
    INS_START,
    INS_END,
    INS_FWD,
    INS_RGT,
}INSTYPE;

typedef struct PROG{
    char input[MAXTOKENSIZE][MAXTOKENSIZE];
    int current_count;

}PROG;



typedef double NUM;

typedef struct FWD
{
    INSTYPE type;
    NUM number;   
}FWD;

typedef struct RGT{
    INSTYPE type;
    NUM number;
}RGT;

typedef union INS
{
    FWD forwarad;
    RGT right;
}INS;

typedef struct INSLST {
    INS instruction;
    INSLST* next;
}INSLST;


void parsePROG(PROG* p);
INSLST* parseINSLST();

void parsePROG(PROG* p){

if (p->input[p->current_count] != "START")
{
    return fprintf(stderr, "Expected a START at the start of the function");
}

p->current_count++;

}

INSLST* parseINSLST()
{

}



int main(void)
{
    return 0;
}