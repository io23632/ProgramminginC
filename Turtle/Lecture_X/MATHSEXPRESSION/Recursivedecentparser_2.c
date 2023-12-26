#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXSTRLEN 1000

typedef struct phrase{
    char current[MAXSTRLEN];
}phrase;


int parseFactor(phrase* p);
int parseProduct(phrase* p);


int main(){

    phrase* p = (phrase*)calloc(1, sizeof(phrase));


    strcpy(p->current, "2*3+4*5");
    int result = parseProduct(p);
    printf("result is: %d\n", result);


    free(p);
    return 0;
}


int parseProduct(phrase* p)
{
    int factor1 = parseFactor(p);
    while (*p->current == '*')
    {
        p++;
        int factor2 = parseFactor(p);
        factor1 = factor1*factor2;
    }
    return factor1;
}

int parseFactor(phrase* p)
{
    for (int i = 0; i < MAXSTRLEN; i++){

        if (p->current[i] >= '0' && p->current[i] <= '9'){
            return p->current[i] - '0';
        }
    }
return -1;
}




