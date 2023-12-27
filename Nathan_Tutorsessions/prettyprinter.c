#include <stdio.h>

/*

Grammar:

<OP> ::= '+' | '-' | '*' | '/'
<VAR> ::= [A-Z]
<LITERAL> ::= Any number 
<EXP> ::= <VAR> | <LITERAL> | <OP><EXP> | <OP><EXP><OP> | '(' <EXP> ')'

*/

typedef enum ExpressionKind{
    uni_expression,
    binary_expression,
    VAR,
    LITERAL,
}ExprKind;

typedef enum UNOP{
    U_MINUS,
}UNOP;

typedef enum BIOP{
    B_PLUS,
    B_TIMES,
    B_MINUS,
    B_DIVIDE
}BIOP;

typedef char Vartype;
typedef double Literaltype;


typedef struct Expr Expr;

typedef struct Uni_Op{
    UNOP op;
    Expr* expression;
}Uni_Op;

typedef struct Bi_Op{
    BIOP op;
    Expr* lhs;
    Expr* rhs;
}Bi_Op;

struct Expr{
    ExprKind kind;
    union {
        Bi_Op bin_expr;
        Uni_Op uni_expr;
        Vartype var;
        Literaltype lit;
    } data;
};



void pretty_printer(Expr* expr)
{

    printf("(");
    switch (expr->kind){
        case VAR: {
            printf("")
        }
    }

    
}




int main(void)
{

    return 0;
}