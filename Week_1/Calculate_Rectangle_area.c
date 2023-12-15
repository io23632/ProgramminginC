
#include <stdio.h>


int main(void )
{
// Calculate the area of a triangle
    int side1, side2, area;
    side1 = 7;
    side2 = 10;
    area = (side1 * side2) / 2;

    char* message;
    message = "I have now calculated the area of the triangle";

    printf("Len of side 1 is %i is meters\n", side1);
    printf("Len of side 2 is %i is metes\n", side2);
    printf("area of rectangle is %i metes\n", area);
    printf("%s", message);

    return 0;


}