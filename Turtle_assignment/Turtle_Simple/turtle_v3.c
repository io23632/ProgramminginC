#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAXTOKENSIZE 10000


/*
GRAMMAR to parse:
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



void parsePROG(prog* p);
void parseINSLST(prog* p);
bool isNUMBER(const char* str);
FWD parseFWD(prog* p);
RGT parseRGT(prog* p);

/*
<PROG> ::= "START" <INSLST>
<INSLST> ::= "END" | <INS> <INSLST>
<INS> ::= <FWD> | <RGT>
<FWD> ::= "FORWARD" <NUM>
<RGT> ::= "RIGHT" <NUM>
<NUM> ::= 10 or -17.99 etc.
*/

int main(int argc, char * argv[])
{

   if (argc < 2)
   {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]); 
    return 1;
   }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Error openining file");
    }

    prog* p = (prog*)malloc(sizeof(prog));
    if (p == NULL) {
        fprintf(stderr, "Memory allocation error");
        fclose(file);
        return 1;
    }

    int i = 0;
    while (fscanf(file, "%s", p->input[i]) == 1) {
        i++;
    }
    p->current_count = 0;
    parsePROG(p);

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


    if (isNUMBER(p->input[p->current_count])) {
        if (sscanf(p->input[p->current_count], "%lf", &fwd_ins.number))
        p->current_count++;
        return fwd_ins;
    }

    else {
        fprintf(stderr, "expexted a number after FORWARD\n");
        exit(1);

    }
}

RGT parseRGT(prog* p)
{
    
    RGT rgt_ins;
    rgt_ins.type = INS_RGT;
    p->current_count++;

    if (isNUMBER(p->input[p->current_count])) {
        if (sscanf(p->input[p->current_count], "%lf", &rgt_ins.number))
        p->current_count++;
        return rgt_ins;
    }

    else {
        fprintf(stderr, "Error: Expected a number after 'RIGHT'\n");
        exit(1);
    }
    
}

bool isNUMBER(const char* str){

    double temp;
    return sscanf(str, "%lf", &temp) == 1;
}
