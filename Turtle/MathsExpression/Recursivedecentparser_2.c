#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXSTRLEN 1000

typedef struct phrase{
    char* current;
}phrase;


int parseFactor(phrase* p);
int parseProduct(phrase* p);
int parseSum(phrase* p);
void free_phrase(phrase* p);


int main(void){

    phrase* p = (phrase*)calloc(1, sizeof(phrase));
    if (p == NULL)
    {
        return -1;
    }

    p->current = calloc(MAXSTRLEN, sizeof(char));
    
    if (p->current == NULL){
        return -1;
    }


    strcpy(p->current, "2*3+4*5");
    
   int result = parseSum(p);
   printf("result is: %d\n", result);

    
    free_phrase(p);
    return 0;
}


int parseProduct(phrase* p)
{
    int factor1 = parseFactor(p);
    while (*p->current == '*')
    {
        p->current++;
        int factor2 = parseFactor(p);
        factor1 = factor1*factor2;
    }
    return factor1;
}

int parseFactor(phrase* p)
{
    if (isdigit(*p->current)){
        int num = *p->current - '0';
        p->current++;
        return num;
        
    }
    return -1;
}


int parseSum(phrase* p)
{
    int product1 = parseProduct(p);

    while (*p->current == '+')
    {
        p->current++;
        int product2 = parseProduct(p);
        product1 = product1 + product2;
    }
    return product1;
    
}


void free_phrase(phrase* p)
{
    free(p);
}