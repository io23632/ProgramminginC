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
    INS_LOOP,
}INSTYPE;

typedef double NUM;
typedef char LTR;
typedef char Op;

typedef struct PROG{
    char input[MAXTOKENSIZE][MAXTOKENSIZE];
    int current_count;
}prog;

typedef struct INSLST INSLST;

typedef union VARNUM{
    LTR variable;
    NUM number;
}VARNUM;

typedef struct WORD {
    char str[MAXTOKENSIZE];
}WORD;

typedef struct ITEM{
    INSTYPE type;
    union {
        VARNUM varnum;
        WORD word;
    }items;
}ITEM;

typedef struct LST{
    ITEM item_data[MAXTOKENSIZE];
    int list_count;
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
}LOOP;

struct INSLST{
    INSTYPE type;
    union {
        FWD fwd;
        RGT rgt;
        COL col;
        SET set;
        LOOP loop;
    } ins;
    struct INSLST* next;
};

void parsePROG(prog* p);
void parseINSLST(prog* p, INSLST** inslst);
bool isNUMBER(const char* str);
bool isVARIABLE(const char* str);
bool isOperation(const char* str);
bool isLetter(const char* str);
void isWORD(prog* p, char str[MAXTOKENSIZE]);
FWD parseFWD(prog* p);
RGT parseRGT(prog* p);
COL parseCOL(prog* p);
SET parseSET(prog* p);
LOOP parseLOOP(prog* p);
void parsePOSTFIX(prog* p, SET* set);
LST parseLST(prog* p);
void parseITEM(prog* p, LST* list);
void freeINSLST(INSLST* head);
void test(void);