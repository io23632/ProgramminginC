#include <stdio.h>



// <PROG>   ::= "START" <INSLST>
// <INSLST> ::= "END" | <INS> <INSLST>
// <INS>    ::= <FWD> | <RGT> | <COL> | <LOOP> | <SET>
//
// <FWD>  ::= "FORWARD" <VARNUM>
// <RGT>  ::= "RIGHT" <VARNUM>
// <COL>  ::= "COLOUR" <VAR> | "COLOUR" <WORD>
// <LOOP> ::= "LOOP" <LTR> "OVER" <LST> <INSLST>
// <SET>  ::= "SET" <LTR> "(" <PFIX>



typedef struct {

} FwdIns;

typedef struct {

} RgtIns;

typedef struct {

} ColIns;

typedef struct {

} LoopIns;

typedef struct {

} SetIns;

typedef enum {
  FWD_INS;
  RGT_INS;
  COL_INS;
  LOOP_INS;
  SET_INS;
} InsKind;

typedef struct {
  // 5 variants
  // What variant am I?
  InsKind ins_kind;
  // Given I know what variant I am, all the data for that variant
  union {
    VarNum var_num; // BOTH FWD and RGT
    ColIns col_ins;
    LoopIns loop_ins;
    SetIns set_ins;
  } body;
} Ins;

int main() {

}