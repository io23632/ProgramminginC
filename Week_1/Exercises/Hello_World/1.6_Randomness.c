#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {

    int median = RAND_MAX / 2;
    int plus_count = 0;
    int minus_count = 0;
    int differnce = 0;

    for (int i = 0; i < 500; i++) {

        if (rand() > median) {
            plus_count++;


        } else (rand() < median); {

            minus_count++;

        }
        differnce = plus_count - minus_count;
        printf("%d\n", differnce);

    }
    printf("Added to plus counter %d\n", plus_count);
    printf("Added to minus counter %d\n", minus_count);

    return 0;


}