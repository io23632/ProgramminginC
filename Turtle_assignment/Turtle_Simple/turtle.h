#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAXTOKENSIZE 1000


typedef enum{
    INS_FWD,
    INS_RGT,
    INS_COL,
    INS_SET,
}INSTYPE;

typedef double NUM;
typedef char LTR;
typedef char Op;

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

typedef struct LST{
    INSTYPE type;
    union {
        VARNUM varnum;
        WORD word;
    }ITEM;
}LST;

typedef struct PFix{
    INSTYPE type;
    union {
        Op symbol;
        VARNUM varnum;
    }precurse;
}PFix;

typedef struct SET{
    INSTYPE type;
    LTR letter;
    PFix postfix[MAXTOKENSIZE];
    int postfix_count;
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

typedef struct LOOP {
    INSTYPE type;
    LTR loop_variable;            // The loop variable
    LST* loop_set;                // The set of values to iterate over
    INSLST* loop_body;            // Pointer to the first instruction in the loop body
    struct LOOP* next;            // Pointer to the next LOOP or instruction
} LOOP;

typedef struct INSLST {
    INSTYPE type;
    union {
        FWD fwd;
        RGT rgt;
        COL col;
        SET set;
    } ins;
    struct INSLST* next;
} INSLST;

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
void parsePOSTFIX(prog* p, SET* set);
LST parseLST(prog* p);
void testParsePROG_ValidInput();
void test(void);