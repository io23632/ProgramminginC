#include <stdio.h>

// Make a pyramid like so:

//  # #
// ## ##
//### ###
// With the height of the pyramid being defined by the user:

void pattern1(int n);
void pattern2(int n);
void pattern3(int n);
void pattern4(int n);
void mario_pattern(int n);

int main(void) {

    mario_pattern(5);


return 0;

}



void mario_pattern(int n){

    for (int row = 0; row < n; row++)
    {
        for (int sp = row; sp < n; sp++) {
            printf(" ");
        }
        for (int col = 0; col <= row; col++) {
            printf("#");
        }
        printf(" ");
        for (int col = 0; col <= row; col++) {
            printf("#");
        }

        printf("\n");
    }

}



void pattern4(int n) {
    // Print the top half of the diamond (including the middle line)
    for (int row = 0; row < n; row++) {
        // Print leading spaces
        for (int sp = 0; sp < n - row - 1; sp++) {
            printf(" ");
        }
        // Print asterisks with spaces
        for (int col = 0; col <= row; col++) {
            printf("* ");
        }
        printf("\n");
    }
    // Print the bottom half of the diamond
    for (int row = n - 2; row >= 0; row--) {
        // Print leading spaces
        for (int sp = 0; sp < n - row - 1; sp++) {
            printf(" ");
        }
        // Print asterisks with spaces
        for (int col = 0; col <= row; col++) {
            printf("* ");
        }
        printf("\n");
    }
}

void pattern3(int n){

/*

#
# #
# # #
# # # #
# # # # #
# # # # # #
# # # #
# # #
# #
#

*/
for (int row = 0; row <= 2*n-1 ; row++)
{
    if (row <= n){
        for (int col = 0; col <= row; col++) {
            printf("# ");
        }
    }
    else if (row > n) {
        for (int col = 0; col < 2*n - row; col++) {
            printf("# ");
        }
    }
    printf("\n");
}
}

void pattern2(int n) {

/*

# # # # 
# # # 
# # 
# 

*/

for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n - i; j++) {
        printf("# ");

        }
    printf("\n");
    }

}


void pattern1(int n) {

/*

# 
# # 
# # # 
# # # # 

*/

for(int i = 0; i <= n; i++) {
    for (int j =0; j <= i; j++) {
        printf("# ");
    }
    printf("\n");
}

}