#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
/**/

#define MAXNUMBTOKENS 100
#define MAXTOKENSIZE 20
/* This is a simplification of the strcmp  */
#define strsame(A,B) (strcmp(A, B) == 0)
/* Here "__FILE__" and "__LINE__" tells you the file and line where the error has occurerd (or where the error was called atleast) and 
the __fun__ will tell you in which function, these are part of C code defined in C99 not a coder defined function */
#define ERROR(PHRASE) {fprintf(stderr, "Fatal Error %s occurerd in %s, line %d\n", PHRASE, __FILE__, __LINE__, __func__);\
exit(EXIT_FAILURE);}

/* struct to read the data to pharse */
typedef struct prog{
    /* Array to store the words given to pharse: */
    char words[MAXTOKENSIZE][MAXTOKENSIZE];
    // counter to count the number of words
    int current_count;
}Program;

/* underlying functions (look at the railroad pdf in this folder): 
There are three functions for the three rules PROG, CODE and STATEMENT*/
/*The underlying grammer for the three functions are* : /
// <PROG> ::= "BEGIN" <CODE>*/
// <CODE> ::= "END" | <STATEMENT><CODE>
// <STATEMENT> ::= "ONE" | "NOUGHT" /* The statements can only be ONE or a NOUGHT */

void Prog(Program* p);
void Code(Program* p);
void Statement(Program* p);

void Prog(Program* p)
{
// p->words are is the array where all the words are stored 
// which word we want is stored in the current word counter
/* "BEGIN" is the grammar of the <PROG> so the this function ensures that we start with the word "BEGIN", if 
not then we exit */ 

    if (!strsame(p->words[p->current_count], "BEGIN"))
    {
        ERROR("Needs a BEGIN statement");
    }
    
}





