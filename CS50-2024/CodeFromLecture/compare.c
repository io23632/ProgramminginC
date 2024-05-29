#include <stdio.h>
#include <ctype.h>

char get_char(char promt[]);

int main(void) {

char response = get_char("Do you agree? ");
char lowerCaseResponse = tolower(response);
printf("%c", response);
if (lowerCaseResponse == 'y'){
    printf("\nAgreed\n");
} else if (lowerCaseResponse == 'n')

{
    printf("Not agreed\n");
}

return 0;
}


char get_char(char promt[]) {
printf("%s", promt);
char character = getchar();
return character;
}