#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAXNUMBTOKENS 100
#define MAXTOKENSIZE 20
/* This is a simplification of the strcmp  */
#define strsame(A,B) (strcmp(A, B) == 0)
/* Here "__FILE__" and "__LINE__" tells you the file and line where the error has occurerd (or where the error was called atleast) and 
the __fun__ will tell you in which function, these are part of C code defined in C99 not a coder defined function */
#define ERROR(PHRASE) {fprintf(stderr, "Fatal Error %s occurerd in %s, line %d\n", PHRASE, __FILE__, __LINE__);\
exit(EXIT_FAILURE);}

/* struct to read the data to pharse */
typedef struct prog{
    /* Array to store the words given to pharse: */
    char words[MAXTOKENSIZE][MAXTOKENSIZE];
    // counter to count the number of words
    int current_count;
}Program;

/* underlying functions (look at the railroad pdf in this folder): */
/* There are three functions for the three rules PROG, CODE and STATEMENT */
/* The underlying grammer for the three functions are : */
// <PROG> ::= "BEGIN" <CODE>
// <CODE> ::= "END" | <STATEMENT><CODE> 
// <STATEMENT> ::= "ONE" | "NOUGHT" 
/* The statements can only be ONE or a NOUGHT */

void Prog(Program* p);
void Code(Program* p);
void Statement(Program* p);

int main(void)
{

// calloc some space for the structure: 

Program* prog = (Program*)calloc(1, sizeof(Program));

if (prog == NULL)
{
    ERROR("MEMORY ALLOCATION FAILURE");
}

int i = 0;
while (scanf("%s", prog->words[i++]) == 1);
Prog(prog);
printf("Pharsed Ok");
free(prog);

return 0;

}

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

// Increment counter, so that everytime you call prog you go through the rest of the statement

    p->current_count++;

/* If the first word is a begin then you call code, becuase that is the grammar of <PROG> */

    Code(p);
}


void Code(Program* p)
{

/* Code is a recrusive function, to get out of code you need an end as stated by the grammar */

    if (strsame(p->words[p->current_count], "END") )
    {
        return;
    }

// If End is not entered, then call statement:

    Statement(p);

// Increment count

    p->current_count++;

// reccusivley call code (which remember calls statement if END is not entered)

    Code(p);
}


/* Added interpreter functionality to the statement function so that some kind of useful feedback is given to the user, this code is 
the interpreter: */

void Statement(Program* p)
{

/* Remember what this ADT is doing: we are writing a programme that pharses a language, in that language 
there are only two things allowed: NOUGHT or ONE, therefore here in statement all we have to do is make sure that ther 
characters entered are either a NOUGHT or a ONE */

    if (strsame(p->words[p->current_count], "ONE") )
    {
        // print statement added: 
        printf("1\n");
        return;
    }

    if (strsame(p->words[p->current_count], "NOUGHT") )
    {
         // print statement added: 
         printf("0\n");
        return;
    }

    else
    {
        ERROR("INVALID CHARACTER EXPECTING A NOUGHT OR ONE");
    }

}

