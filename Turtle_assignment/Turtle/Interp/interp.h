#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>
#define BASE_KEY 'A'
#define MAX_KEY 'Z'
#define KEY_RANGE (MAX_KEY - BASE_KEY + 1)
#define KEY(x) (x - 'A')


#define MAXTOKENSIZE 1000
#define GRID_WIDTH 51
#define GRID_HEIGHT 33
// #define GRID_HEIGHT 100 // This workds
//#define M_PI 3.14159265358979323846

typedef enum{
    INS_FWD,
    INS_RGT,
    INS_COL,
    INS_SET,
    INS_LOOP,
}INSTYPE;

typedef enum{
    NUMBER,
    VARIABLE,
    OPERATION,
    Word,
}POSTFIXTYPE;

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
    POSTFIXTYPE type;
    union {
        VARNUM varnum;
        WORD word;
        LTR letter;
    }items;
}ITEM; 

typedef struct LST{
    ITEM item_data[MAXTOKENSIZE];
    int list_count;
}LST;

typedef struct PFix{
    POSTFIXTYPE type;
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
    POSTFIXTYPE type;
    VARNUM varnum;
}RGT;

typedef struct FWD{
    POSTFIXTYPE type;
    VARNUM varnum;
}FWD;


typedef struct LOOP {
    LTR loop_variable;            // The loop variable
    LST* loop_set;                // The set of values to iterate over
    INSLST* loop_body;            // Pointer to the first instruction in the loop body  
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

typedef struct TurtleState{
    NUM x;
    NUM y;
    NUM angle;
    char colour; 
}TurtleState;

typedef struct grid{
    char pixel[GRID_WIDTH][GRID_HEIGHT];
}grid;

typedef struct env{
    union {
        double num_mapping[KEY_RANGE]; // assign numbers (in double form to the letters in the KEY RANGE)
        LTR ltr_mapping[KEY_RANGE]; // assign char i.e. variables e.g. $B to the letters in KEY RANGE, where LTR is typedef char LTR
        WORD word_mapping[KEY_RANGE]; // assign words to the letters in the key range 
    }env_list;
    int assigned[KEY_RANGE];
    int assigned_keycount;
}env;

typedef struct stack
{
    NUM arr[MAXTOKENSIZE];
    int size;
}stack;


void parsePROG(prog* p, INSLST** head);
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

//////////Interpreter functions//////
void interp(INSLST* inslst, TurtleState* state, env* e, grid* g, stack* stck);
void go_fwd(TurtleState* state, FWD fwd_interp, grid* g, env* e);
void turn_rgt(TurtleState* state, RGT rgt_ins, env* e);
bool inbounds(NUM x1, NUM y1);
void linedraw(int x1, int y1, int x2, int y2, grid* g, char c);
void initilgrid(grid* g);
void printgrid(grid* g);
void set_col(TurtleState* state, COL col_interp);
void interp_loop(LOOP* loop, TurtleState* state, env* e, grid* g, stack* stck);
void interp_set_env(env* e, SET* s, stack* stck);
double evaluate_postfix(env* e, SET* set, stack* stck);

void init_env(env* e);
void check_key(env* e, char key);
double getkey_number(env* e, char key);
LTR getkey_letter(env* e, char key);
WORD getkey_word(env* e, char key);
Op getkey_(env* e, char key);
void setkey_number(env* e, char key, double d);
void setkey_letter(env* e, char key, LTR l);
void setkey_word(env* e, char key, WORD word);
void setkey_Op(env* e, char key, Op operation);

stack* init_stack(void);
void stack_push(stack* s, NUM number);
double stack_pop(stack* s);
void interp_set(stack* s, SET* set);

void test(void);
