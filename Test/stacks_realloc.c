#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define ELEMSIZE 20
#define STACKTYPE "Realloc"

#define FIXEDSIZE 16
#define SCALEFACTOR 2
#define DOTFILE 5000

typedef int stacktype;


typedef struct stack{
    // Underlying array;
    stacktype* a;
    int size; 
    int capacity;
}stack;

/* Create an empty stack */
stack* stack_init(void);
/* Add element to top */
void stack_push(stack* s, stacktype i);
/* Take element from top */
bool stack_pop(stack* s, stacktype* d);
/* Clears all space used */
bool stack_free(stack* s);

/* Optional? */

/* Copy top element into d (but don't pop it) */
bool stack_peek(stack*s,  stacktype* d);
/* Make a string version - keep .dot in mind */
void stack_tostring(stack*, char* str);

stack* stack_init(void)
{
    //assign memory to the stack struct
    stack* s = (stack*)calloc(1, sizeof(stack));
    // if NULL return 
    if (s == NULL) {
        fprintf(stderr, "Memory allocation failure");
    }
    // assign memory to the array
    s->a = (int*)calloc(FIXEDSIZE, sizeof(int));
    // set current size to 0
    s->size = 0;
    // set capacity (current) to the fixedsize 
    s->capacity = FIXEDSIZE;

    return s;
}

void stack_push(stack* s, stacktype d)
{

    if (s == NULL) {
            return; 
        }

    if (s->size >= s->capacity) {
        s->a = (int*)realloc(s->a, sizeof(int)*s->capacity*SCALEFACTOR);
        s->capacity = s->capacity*SCALEFACTOR;
    }
    if (s->a == NULL) {
            return; 
        }

    s->a[s->size] = d;
    s->size++;
}

bool stack_pop(stack* s, stacktype* d)
{
    if (s == NULL || s->size < 1) {
        return false;
    }

    *d = s->a[s->size];
    s->size--;
    return true;
}

bool stack_peek(stack* s, stacktype* d)
{
    if (s == NULL || s->size <= 0) {
        return false;
    }

    *d = s->a[s->size - 1];
    return true; 

}

void stack_tostring(stack* s, char* str)
{
    /* The string format this function will create: "d|d|d" */
    //create an initial temp array that is local to this function
    char temp[ELEMSIZE];
    // the pointer array str (that can be called in main) is initialised with a null character
    str[0] = '\0';

    if (s == NULL || s->size < 1){
        return;
    }

    for (int i=s->size - 1; i >=0; i--) 
    {
        /* The sprintf function here looks like a print function but rather than printing 
        it will put the argments in a string, here we are putting, digits in the stack 
        (from s->a[i]) in temp array */
        sprintf(temp, "%d", s->a[i]);
        /* concats the temporary array we made to the str array */
        strcat(str, temp);

        strcat(str, "|");
    }

    /* The loop above will produce: "d|d|d|" we want: "d|d|d " so the last character in the string 
    the "|" is replaced with a null char */
    str[strlen(str)-1] = '\0';
}

bool stack_free(stack* s)
{
    if (s == NULL){
        return true;
    }

    free(s->a);

    free(s);

    return true;
}


