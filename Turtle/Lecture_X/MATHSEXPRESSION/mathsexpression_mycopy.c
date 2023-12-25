#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXEXPR 400
#define ON_ERROR(S) {fprintf(stderr, "%s", S); \
exit(EXIT_FAILURE); }

typedef struct prog{
    char str[MAXEXPR];
    int count;
}Programme;

/* The grammer is:

<EXPRESSION> ::= <EXPRESSION><OPERATOR><EXPRESSION> | "(" <EXPRESSION> ")" | "-"<EXPRESSION> | <LETTER>
<LETTER> ::= "A-Z"
<OPERATOR> ::= "+" | "-" | "/" | "*" 

*/


bool isop(Programme* p, char c);
void expression(Programme* p);

int main(void)
{
    Programme p;
    p.count = 0;
    /*
    Here we are seeing the use of square brackets in the scanf function: 
    These square brackets mean everything that is allowed to be passed in the string: 
    So characters A to Z are allowed 
    -, +, () are allowed
    */
    if (scanf("%[A-Z-+()]", p.str) != 1){
        ON_ERROR("Could not read expression \n");
    }

    // expression(&p);
    printf("Parsed OK \n");

    return 0;
}

bool isop(Programme *p, char c)
{
    // Check if the character at the current position is one of the operators
    if (p->str[p->count] == '+' || p->str[p->count] == '-' || 
        p->str[p->count] == '*' || p->str[p->count] == '/') {
        return true;
    }

    // If the character provided (c) does not match the current character in the program,
    // and the current character is not an operator, then raise an error.
    if (p->str[p->count] != c) {
        ON_ERROR("I was expecting a different character\n");
    }

    return false;
}

void expression(Programme* p)
{



}

// void Expr(Prog *p)
// {
//    if(p->str[p->count] == '('){
//       p->count = p->count + 1;
//       Expr(p);
//       p->count = p->count + 1;
//       if(p->str[p->count] != ')'){
//          ON_ERROR("I was expecting a ) ?\n");
//       }
//    }

//    else if(p->str[p->count] == '-'){
//       p->count = p->count + 1;
//       Expr(p);
//    }

//    // Note Look-Ahead
//    else if(isop(p->str[p->count+1])){
//       if(isupper(p->str[p->count])){
//          p->count = p->count + 1;
//          Op(p);
//          p->count = p->count + 1;
//          Expr(p);
//       }
//    }

//    else{

//       if(!isupper(p->str[p->count]) ||
//          isupper(p->str[p->count+1])){
//          ON_ERROR("Expected a single letter ?\n");
//       }
//    }

// }


