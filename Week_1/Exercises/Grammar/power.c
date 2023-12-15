#include <stdio.h>
#define LOOPEND 10

int main(void)

{
    int i = 1;
    int power = 1;

    while (i <= LOOPEND) {
        power = power * 2;
        printf("%5i", power);
        ++i;
    }
    printf("\n");
    return 0;

}