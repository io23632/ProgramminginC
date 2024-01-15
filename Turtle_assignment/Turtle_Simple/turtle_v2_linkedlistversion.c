#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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
    INS_FWD,
    INS_RGT,
}INSTYPE;

typedef double NUM;

typedef union TokenType{
    char str[MAXTOKENSIZE];
    NUM num;
}TokenType;

typedef struct PROG{
    TokenType input[MAXTOKENSIZE];
    int current_count; 
}prog;

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
    union {
        FWD* forward;
        RGT* right;
    } instruction;
    struct INSLST* next;
}INSLST;


void parsePROG(prog* p);
INSLST* parseINSLST(prog* p);
bool isNUMBER(const char* str);
FWD* parseFWD(prog* p);
RGT* parseRGT(prog* p);

int main(void) 
{
    prog* p = (prog*)malloc(sizeof(prog));
    if (p == NULL) {
        return -1;
    }

    int i = 0;
    while (scanf("%s", p->input[i].str) == 1) {
        i++;
    }
    parsePROG(p);
    free(p);

    return 0;
}

void parsePROG(prog* p)
{
    
    // Check if the first token is start:
    if (strcmp((p->input[p->current_count].str), "START") != 0){
        fprintf(stderr, "EXPECTED A START");
        exit(1);
    }

    else {
        p->current_count++;
        parseINSLST(p);
    }

}

INSLST* parseINSLST(prog* p)
{
    if (strcmp(p->input[p->current_count].str, "END") == 0){
        printf("Programe finished\n");
        return NULL;
    }
    // create a INS LST:
    INSLST* ins_list = (INSLST*)malloc(sizeof(INSLST)); /// Do I need to free INSLST or will that will willl free(p) in main achieve the same result?
    // FORWARD INSTRUCTION

    if (ins_list == NULL){
        fprintf(stderr, "Memory allocation failure");
        exit(1);
    }

    if (strcmp(p->input[p->current_count].str, "FORWARD") == 0) {
        ins_list->instruction.forward = parseFWD(p);
        ins_list->next = parseINSLST(p);
    }
    // RIGHT INSTRUCTION
    else if (strcmp(p->input[p->current_count].str, "RIGHT") == 0) {
        ins_list->instruction.right = parseRGT(p);
        ins_list->next = parseINSLST(p);
    }
    //INVALID TOKEN
    else {
        fprintf(stderr, "INVALID TOKEN %s \n", p->input[p->current_count].str);
        exit(1);
    }
    //Increment count to next token
    // recursivley call INSLST
    return ins_list;

}

FWD* parseFWD(prog* p){

FWD* fwd_ins = (FWD*)malloc(sizeof(FWD));

if (fwd_ins == NULL) {
    return NULL;
}

fwd_ins->type = INS_FWD;
p->current_count++;

if (isNUMBER(p->input[p->current_count].str)) {
    if (sscanf(p->input[p->current_count].str, "%lf", &fwd_ins->number) == 1)
        p->current_count++;
        return fwd_ins;
    

}

else {

    fprintf(stderr, "Error: Expected a number after 'FORWARD'\n");
    free(fwd_ins); // Free the allocated memory in case of error
    return NULL;
} 

}

RGT* parseRGT(prog* p){

RGT* rgt_ins = (RGT*)malloc(sizeof(RGT));

if (rgt_ins == NULL){
    return NULL;
}

rgt_ins->type = INS_RGT;
p->current_count++;

if (isNUMBER(p->input[p->current_count].str)) {
    if (sscanf(p->input[p->current_count].str, "%lf", &rgt_ins->number) == 1)
    p->current_count++;
    return rgt_ins;
}

else {

    fprintf(stderr, "Error: Expected a number after 'RIGHT'\n");
    free(rgt_ins); // Free the allocated memory in case of error
    return NULL;
}

}

bool isNUMBER(const char* str){

    double temp;
    return sscanf(str, "%lf", &temp) == 1;
}
