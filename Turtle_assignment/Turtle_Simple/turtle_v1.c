#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAXTOKENSIZE 20
/*
<PROG> ::= "START" <INSLST>
<INSLST> ::= "END" | <INS> <INSLST>
<INS> ::= <FWD> | <RGT>
<FWD> ::= "FORWARD" <NUM>
<RGT> ::= "RIGHT" <NUM>
<NUM> ::= 10 or -17.99 etc.
*/

typedef enum{
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

typedef struct INSLST {
    INSTYPE type;
    union {
        FWD* forward;
        RGT* right;
    } instruction;
    struct INSLST* next;
}INSLST;


void parsePROG(PROG* p);
INSLST* parseINSLST(PROG* p);
FWD* parseFWD(PROG* p);
RGT* parseRGT(PROG* p);

int main(void)
{

    PROG* P = (PROG*)malloc(sizeof(PROG));
    P->current_count = 0;

    if (P == NULL){
        fprintf(stderr, "Memory allocation failure");
        return 1;
    }

    int i = 0;
    while (scanf("%s", P->input[i]) == 1){
        i++;
    }
    parsePROG(P);
    printf("PARSED OKAY");
    free(P);

    return 0;
}

void parsePROG(PROG* p){

if (strcmp(p->input[p->current_count], "START") != 0)
{
    fprintf(stderr, "Expected a START at the start of the function");
    exit(1);
}

p->current_count++;
parseINSLST(p);

}

INSLST* parseINSLST(PROG* p)
{

if (strcmp(p->input[p->current_count], "END") != 0) {
    fprintf(stderr, "PROGRAMME END");
    return NULL;
}

else {
INSLST* ins_list = (INSLST*)malloc(sizeof(INSLST));
if(ins_list == NULL){
    return NULL;
}
//FORWARD INSTRUCTION
if (strcmp(p->input[p->current_count], "FORWARD") == 0) {
    ins_list->type = INS_FWD;
    ins_list->instruction.forward = parseFWD(p);
}
// RIGHT INSTRUCTION
if (strcmp(p->input[p->current_count], "RIGHT")) {
    ins_list->type = INS_FWD;
    ins_list->instruction.right = parseRGT(p);
}

p->current_count++;
ins_list->next = parseINSLST(p);

return ins_list;
free(ins_list);
}

}

FWD* parseFWD(PROG* p)
{
    FWD* fwd_ins = (FWD*)malloc(sizeof(FWD));
    fwd_ins->type = INS_FWD;
    // look at the next token containing the NUM
    p->current_count++;
    // if the next number is a digit 
   if (isdigit((p->input[p->current_count]))) {
        if (sscanf(p->input[p->current_count], "%lf", &fwd_ins->number) == 1) {
        //move to the next token:
        p->current_count++;
        return fwd_ins;
    }
    else {
        fprintf(stderr, "Expected a Valid number after instructions");
        return NULL;
    }
    // Add code for interpreter:
   }
free (fwd_ins); // do I need to free it here or can I free the PROG structure in main which will then free FWD?
}
