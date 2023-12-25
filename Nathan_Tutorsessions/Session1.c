#include <stdio.h>

// <OP> := '+' | ...
//
// <VAR> := [a-z]
//
// <LITERAL> := %lf double
//
// <EXP> := <VAR>
//        | <LITERAL>
//        | <OP> <EXP>        -- unary operation -x
//        | <EXP> <OP> <EXP>  -- binary operation x + 3
//        | '(' <EXP> ')'

typedef enum expr_kind {
  VAR,
  LITERAL,
  UNOP,
  BINOP,
} ExprKind;

typedef enum unnop {
  U_MINUS
} UnOp;

typedef enum binop {
  B_PLUS,
  B_TIMES,
  B_MINUS,
  B_DIVIDE
} BinOp;

typedef struct expr {
  ExprKind kind;

  // BinaryExpr* bin_expr;
  // UnaryExpr* un_expr;
  // char* var_name;
  // double* literal;

  void* body;
} Expr;

typedef struct un_expr {
  UnOp opcode;
  Expr* operand;
} UnaryExpr;

typedef struct bin_expr {
  BinOp opcode;
  Expr* lhs;
  Expr* rhs;
} BinaryExpr;

void print_expr(Expr* expr) {
  printf("(");
  switch (expr->kind) {
    case VAR: {
      char *var_name = (char*) expr->body;
      printf("%c", *var_name);
      break;
    }
    case LITERAL: {
      double* literal = (double*) expr->body;
      printf("%lf", *literal);
      break;
    }
    case UNOP: {
      UnaryExpr* un_expr = (UnaryExpr*) expr->body;
      switch (un_expr->opcode) {
        case U_MINUS:
          printf("-");
          break;
      }

      print_expr(un_expr->operand);
      break;
    }
    case BINOP: {
      BinaryExpr* bin_expr = (BinaryExpr*) expr->body;
      // LHS
      print_expr(bin_expr->lhs);
      // Operation
      switch (bin_expr->opcode) {
        case B_PLUS:
          printf("+");
          break;
        case B_TIMES:
          printf("*");
          break;
        case B_MINUS:
          printf("-");
          break;
        case B_DIVIDE:
          printf("/");
          break;
      }
      // RHS
      print_expr(bin_expr->rhs);

      break;
    }
  }
  printf(")");
}

int main() {

  // (a + b) * 5
  // EXPECTED OUT: (((a)+(b))*(5))

  char a = 'a', b = 'b';
  double five = 5;

  Expr a_expr = {
    .kind = VAR,
    .body = (void*) &a,
  };

  Expr b_expr = {
    .kind = VAR,
    .body = (void*) &b,
  };

  BinaryExpr a_plus_b_body = {
    .opcode = B_PLUS,
    .lhs = &a_expr,
    .rhs = &b_expr,
  };

  Expr a_plus_b = {
    .kind = BINOP,
    .body = (void*) &a_plus_b_body,
  };

  Expr five_expr = {
    .kind = LITERAL,
    .body = (void*) &five,
  };

  BinaryExpr a_plus_b_times_five_body = {
    .opcode = B_TIMES,
    .lhs = &a_plus_b,
    .rhs = &five_expr,
  };

  Expr a_plus_b_times_five = {
    .kind = BINOP,
    .body = (void*) &a_plus_b_times_five_body,
  };

  print_expr(&a_expr);
  printf("\n");
  print_expr(&b_expr);
  printf("\n");
  print_expr(&a_plus_b);
  printf("\n");
  print_expr(&a_plus_b_times_five);
}