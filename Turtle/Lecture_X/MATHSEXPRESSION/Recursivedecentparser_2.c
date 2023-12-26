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


int main(){

    phrase* p = (phrase*)calloc(1, sizeof(phrase));
    p->current = calloc(MAXSTRLEN, sizeof(char));  // Allocate memory for the string
    strcpy(p->current, "2*3+4*5");
    
   int result = parseProduct(p);

   printf("result is: %d/n", result);

    
    free(p->current);
    free(p);
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




