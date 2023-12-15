#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int find_max(int n);

int main(void) {
    int n, max_value;
    printf("how many values do you want to input: ");
    scanf("%d", &n );
    printf("Enter %d real numbers: ", n);

    max_value = find_max(n);
    printf("max_value is %d: ", max_value);
    return 0;
}
    int find_max(int n) {
        int count = 0;
        int max_value = 0;
        int number;

        for (int i = 0; i < n; i++) {
            scanf("%d", &number);

            if (number >= max_value) {
                max_value = number;
                count++;
            }
        }
        return max_value;
        }