#include <stdio.h>

void make_meow(int n);

int main(void) {

printf("How many times would you like to print? ");

int n;

scanf("%i", &n);

make_meow(n);

return 0;
}


void make_meow(int n) {

    for (int i = 0; i < n; i++) {
        printf("meow\n");
    }
}