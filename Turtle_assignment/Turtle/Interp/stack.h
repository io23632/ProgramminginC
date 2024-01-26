#include "interp.h"

typedef struct stack
{
    NUM arr[MAXTOKENSIZE];
    int size;
}stack;

stack* init_stack(void);
void stack_push(stack* s, NUM number);
void interp_set(stack* s, SET* set);