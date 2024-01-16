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
<INS> ::= <FWD> | <RGT> | <COL> | <SET> | <LOOP>
<FWD> ::= "FORWARD" <VARNUM>
<RGT> ::= "RIGHT" <VARNUM>
<COL> ::= "COLOUR" <VAR> | "COLOUR" <WORD>
<VARNUM> ::= <VAR> | <NUM>
<VAR> ::= $<LTR>
<LTR> ::= A, B, ....... Z
<NUM> ::= 10 or -17.99 etc.
<WORD> ::= "RED", "BLUE" , "HELLO!" or "178"
<SET> ::= "SET" <LTR> "(" <PFIX>
<ITEMS> ::= "}" | <ITEM><ITEMS>
<ITEM> ::= <VARNUM> | <WORD>
<PFIX> ::= ")" | <OP><PFIX> | <VARNUM><PFIX>
<OP> ::= "+" | "-" | "*" | "/" 

*/

typedef enum{
    INS_FWD,
    INS_RGT,
    INS_COL,
    INS_SET,
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

typedef union VARNUM{
    LTR variable;
    NUM number;
}VARNUM;

typedef struct WORD {
    char* str;
}WORD;


typedef struct SET{
    INSTYPE type;
    LTR letter;
}SET;

typedef struct COL{
    INSTYPE type;
    union {
        LTR variable;
        WORD word;
    }COL_postfix;
}COL;

typedef struct RGT{
    INSTYPE type;
    VARNUM varnum;
}RGT;

typedef struct FWD{
    INSTYPE type;
    VARNUM varnum;
}FWD;

typedef struct PFix{
    INSTYPE type;
    union {
        OP symbol;
        VARNUM varnum;
    }precurse;
}PFix;

void parsePROG(prog* p);
void parseINSLST(prog* p);
bool isNUMBER(const char* str);
bool isVARIABLE(const char* str);
bool isOperation(const char* str);
bool isLetter(const char* str);
FWD parseFWD(prog* p);
RGT parseRGT(prog* p);
COL parseCOL(prog* p);
SET parseSET(prog* p);
PFix parsePOSTFIX(prog* p);

void test(void);

int main(void)
{

    test();

    prog* p = (prog*)malloc(sizeof(prog));
    p->current_count = 0;

    if (p == NULL){
        fprintf(stderr, "Memory allocation failure");
        return 1;
    }

    int i = 0;
    while (scanf("%s", p->input[i]) == 1){
        i++;
    }
    parsePROG(p);
    printf("PARSED OKAY");
    free(p);

    return 0;
}


void parsePROG(prog* p)
{
    if (strcmp(p->input[p->current_count], "START") != 0) {
        fprintf(stderr, "Expected a START ");
        exit(1);
    }
   
    else {
        p->current_count++;
        parseINSLST(p);
    }
   
}

void parseINSLST(prog* p)
{

    if (strcmp(p->input[p->current_count], "END") == 0) {
        printf("\nPrograme Finished\n");
        exit(0);
    }

    else if (strcmp(p->input[p->current_count], "FORWARD") == 0)
    {
        parseFWD(p);
        parseINSLST(p);
    }

    else if (strcmp(p->input[p->current_count], "RIGHT") == 0)
    {
        parseRGT(p);
        parseINSLST(p);
    }

    else if (strcmp(p->input[p->current_count], "COLOUR") == 0) {
        parseCOL(p);
        parseINSLST(p);
    }

    else if (strcmp(p->input[p->current_count], "SET") == 0 ) {
        parseSET(p);
        parseINSLST(p);

    }
    
    else {
        fprintf(stderr, "INVALID TOKEN / EXPECTED A END\n");
        exit(1);
    }
}

FWD parseFWD(prog* p)
{
    FWD fwd_ins;
    fwd_ins.type = INS_FWD;
    p->current_count++;

    // if there is a number following the FORWARD Instruction:
    if (isNUMBER(p->input[p->current_count])) {
        if (sscanf(p->input[p->current_count], "%lf", &fwd_ins.varnum.number))
        p->current_count++;
        return fwd_ins;
    }
    // if there is a variable following the FORWARD Instruction:
    else if (isVARIABLE(p->input[p->current_count])) {
        if (sscanf(p->input[p->current_count], "%s", &fwd_ins.varnum.variable))
        p->current_count++;
        return fwd_ins;
    }

    else {
        fprintf(stderr, "expexted a number after FORWARD\n");
        exit(1);

    }
}


// what an interpreter function might look like for fwd :
//void gofwd_(FWD* f, turle* t);

RGT parseRGT(prog* p)
{
    
    RGT rgt_ins;
    rgt_ins.type = INS_RGT;
    p->current_count++;

    // if there is a number following the RIGTH Instruction:
    if (isNUMBER(p->input[p->current_count])) {
        if (sscanf(p->input[p->current_count], "%lf", &rgt_ins.varnum.number))
        p->current_count++;
        return rgt_ins;
    }
    // if there is a variable following the RIGTH Instruction:
    else if (isVARIABLE(p->input[p->current_count])) {
        if (sscanf(p->input[p->current_count], "%s", &rgt_ins.varnum.variable))
        p->current_count++;
        return rgt_ins;
    }

    else {
        fprintf(stderr, "Error: Expected a variable or a number after 'RIGHT'\n");
        exit(1);
    }
    
}

COL parseCOL(prog* p)
{
    COL col_ins;
    col_ins.type = INS_COL;
    p->current_count++;

    // Check if it is a variable:
    if (isVARIABLE(p->input[p->current_count])) {
        if (sscanf(p->input[p->current_count], "%s", &col_ins.COL_postfix.variable))
        p->current_count++;
        return col_ins;
    }
    
    // Check if it is a word:
    else {
        sscanf(p->input[p->current_count], "%s", col_ins.COL_postfix.word.str);
        p->current_count++;
        return col_ins;
    }
}

SET parseSET(prog* p)
{

SET set; 
set.type = INS_SET;
p->current_count++;

//parse the letter and move on to parsePFIX
if (isLetter(p->input[p->current_count])) {
    p->current_count++;
    if(strcmp(p->input[p->current_count], "(") == 0)
    parsePOSTFIX(p);
}

else {
    fprintf(stderr, "\nexpected a ( at the begeinng of statement %s:    ", p->input[p->current_count]);
    exit(1);
}

return set;

}

PFix parsePOSTFIX(prog* p)
{
    PFix pfix;
    p->current_count++;

    if (strcmp(p->input[p->current_count], ")") == 0) {
        return pfix;
    }

    // if p.input[p.current_count] == number
    else if (isNUMBER(p->input[p->current_count])) {
        p->current_count++;
        parsePOSTFIX(p);
    }

    // if p.input[p.current_count] == variable 
    else if (isVARIABLE(p->input[p->current_count])) {
        p->current_count++;
        parsePOSTFIX(p);
    }

    // if p.input[p.current_count] == operation
    else if (isOperation(p->input[p->current_count])) {
        p->current_count++;
        parsePOSTFIX(p);
    }

    else {
        fprintf(stderr, "expected valid token for postfix expression at %s    ", p->input[p->current_count]);
        exit(1);
    }

return pfix;
}


bool isOperation(const char* str)
{

if (((strcmp(str, "+") == 0)|| (strcmp(str, "-") == 0)||(strcmp(str, "*") == 0)|| (strcmp(str, "/") == 0))) {
    return true;
}
return false;

}

bool isNUMBER(const char* str){

    double temp;
    return sscanf(str, "%lf", &temp) == 1;
}

bool isVARIABLE(const char* str) {
    
if (str[0] == '$') {
    for (int i = 1; str[i] != '\0'; i++) {
        if (!isupper(str[i])) {
            return false;
        }
    }
    return true;
}
return false;
}

bool isLetter(const char* str)
{
    
    for (int i = 0; i < str[i] != '\0'; i++) 
    {
        if ((isupper(str[i]) && str[i] >= 65 && str[i] <= 95)){
            return true;
        }
    }
    
    return false;
}

void test(void) 
{

    
    assert(isNUMBER("10") == true);
    assert(isNUMBER("17.9987") == true);

    assert(isVARIABLE("$A") == true);
    assert(isVARIABLE("A") == false);
    assert(isVARIABLE("$a") == false);
    assert(isVARIABLE("$Z") == true);

    assert(isOperation("+") == true);
    assert(isOperation("/") == true);
    assert(isOperation("*") == true);
    assert(isOperation("-") == true);
    

    assert(isLetter("A") == true);
    assert(isLetter("a") == false); 
    assert(isLetter("B") == true);
    assert(isLetter("b") == false);
    assert(isLetter("Y") == true);
    assert(isLetter("y") == false);
    assert(isLetter("U") == true);
    assert(isLetter("u") == false);
}