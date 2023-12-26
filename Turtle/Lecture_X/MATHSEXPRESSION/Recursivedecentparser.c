#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

/* We will be writing a simple recursive decent parser for evaluating math formulae
The expression example we want to look at: 2*3+4*5
This we will breakdown into the functions: 
Evaluate Sum : ParseSum()
Evaluate Product: ParseProduct()
Evaluate Factor: ParseFactor()
*/

int parseSum();
int parseProduct();
int parseFactor();

char* x; 


int main()
{

x = "2*3+4*5";

int result = parseProduct();
printf("result is: %d\n", result);


return 0;

}


int parseProduct()
{
    int factor1 = parseFactor();
    int result; 
    while (*x == '*')
    {
        x++;
        int factor2 = parseFactor();

        factor1 = factor1 * factor2; 
    }

return factor1;
}


int parseFactor()
{
    if (*x >= '0' && *x <= '9') 
    {
        return *x++ - '0';
    }
    else{
        printf("expected a integer value ");
        return - 1;
    }
}

int parseSum()
{
    int product1 = parseProduct(); 
    while (*x == '+')
    {
        x++;
        int product2 = parseProduct();

        product1 = product1 + product2;
        
    }
    
    return product1;

}