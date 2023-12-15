#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define FORMATSTR "%i"
#define ELEMSIZE 20
#define STACKTYPE "Linked"



/* Struct to contain linked list */

typedef struct dataframe{
    int i;
    struct dataframe* next;
}dataframe;

typedef struct stack{
    dataframe* start;
    int size;
}stack;


/* Create an empty stack */
stack* stack_init(void);
/* Add element to top */
void stack_push(stack* s, int d);
/* Take element from top */
bool stack_pop(stack* s, int* d);
/* Clears all space used */
bool stack_free(stack* s);

/* Copy top element into d (but don't pop it) */
bool stack_peek(stack*s,  int* d);
/* Make a string version - keep .dot in mind */
void stack_tostring(stack* s, char* str);


stack* stack_init(void)
{void stack_tostring(stack* s, char* str);
   // assign memory to the struct stack 
   stack *s = (stack*)calloc(1, sizeof(stack));
   if (s == NULL) {
    return;
   }
   return s;
}

void stack_push(stack* s, int d)
{

// assign a pointer to a the linked list node; 

dataframe* f = (dataframe*)calloc(1, sizeof(dataframe));
// assing the integer space of the linked list node to the integer entered by user: 
f->i = d;
// point the address part of the node to s->start which is a pointer to the start of the stack
f->next = s->start;
s->start = f;
s->size++;

}


bool stack_pop(stack* s, int* d)
{

   if((s==NULL) || (s->start==NULL)){
      return false;
   }

  /* 1) Create an additional pointer to the start: */
  dataframe* f = s->start->next;
  /* 2) free the s->start */
  free(s->start);
  /* Move along to the next pointer: */
  s->start = f;
  /* Reduce the size of the stack */
  s->size--;


}


bool stack_peek(stack*s,  int* d)
{
     if((s==NULL) || (s->start==NULL)){
      return false;
   }
   
   *d = s->start->i;
   return true;
}


void stack_tostring(stack* s, char* str)
{
    char temp[ELEMSIZE];
    str[0] = '\0';

    if (s == NULL || s->start == NULL) {
        return;
    }
    /* While the pointer s->start is not null which is when we have reached the end of the linked list */
    while (s->start !=NULL)
    {
        sprintf(temp, "%d", s->start->i);
        strcat(str, temp);
        strcat(str, "|");
        s = s->start->next;
    }
    str[strlen(str - 1)] = '\0';
}


bool stack_free(stack* s)
{

if(s){
    dataframe* p = s->start;
    while (p != NULL)
    {
        dataframe* temp = p->next;
        free(p);
        p = temp;
    }
    free(s);
    
}
return true;
}