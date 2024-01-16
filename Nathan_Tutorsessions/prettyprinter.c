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
            printf("%c", expr->data.var);
        }
        case LITERAL: {
            printf("%lf", expr->data.lit);
        }
        case binary_expression: {
           Bi_Op bi_expr  = (expr->data.bin_expr); 
            pretty_printer(bi_expr.lhs);
            switch (bi_expr.op) {
                case B_PLUS: {
                    printf("+");
                }
                case B_MINUS: {
                    printf("-");
                }
                case B_TIMES: {
                    printf("*");
                }
                case B_DIVIDE: {
                    printf("/");
                }
            }
            pretty_printer(bi_expr.rhs);
        }
        case uni_expression: {
            Uni_Op uni_expr = expr->data.uni_expr;
            switch (uni_expr.op) {
                default: printf("-");
            }
            pretty_printer(uni_expr.expression);
            
        }
}




int main(void)
{

    return 0;
}