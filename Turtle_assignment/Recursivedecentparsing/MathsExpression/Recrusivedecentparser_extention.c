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

Adding functionality to take into account: 

- multi-digit numbers e.g. 190 done
- decimal points done
- substraction 
- divison 
- negative 
-exponentitation 

- error handeling
*/

int parseSum();
int parseProduct();
int parseFactor();
int parseNumber();

char* x; 


int main()
{

x = "6.123";

int result = parseNumber();
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
        return parseNumber();
    }
    /* if it contains a bracket, skip the bracket and evaluate the expression inside 
    by recrusively calling the parseFactor function */ 
    else if (*x == '(')
    {
        x++;
        int sum = parseSum();
        // skip closing brackets:
        x++;
        return sum;
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

int parseNumber()
{

/*  A multi digit number e.g. 123 is made up like this: 
1*100 + 2*10 + 3
OR 
(1*10 + 2)* 10+ 3
OR
((0*10 + 1)*10 + 2)*10 + 3
*/  

    // number = number * 10 + number 
    // so for the '1' of 123, 1 * 10 + 1, 
    // increment to the next digit which is 2 and repeat 

// If whole number: 
    double number = 0;
    while(isdigit(*x)){
        number = number * 10;
        number = *x - '0' + number;
        // increment the pointer: 
        x++;
    }
// if decimeal e.g 0.123
// OR 1*0.1 + 2*0.01 + 3* 0.001

if (*x == '.'){
    // move past it:
    x++;
    double factor = 1;
    while (isdigit(*x))
    {
        factor = factor / 10;
        double scaled = (*x - '0') * factor;
        number = number + scaled;
        x++;
    }
     
}

    return number;
}