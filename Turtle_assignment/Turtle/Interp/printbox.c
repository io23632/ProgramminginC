#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXGRID 20

struct Grid{
    char pixel[MAXGRID][MAXGRID];
};


typedef struct Grid grid;
void linedraw(int x1, int y1, int x2, int y2, grid* g);
void initilgrid(grid* g);
void printgrid(grid* g);




int main(int argc, char* argv[])
{

grid g;
initilgrid(&g);
linedraw(9, 9, 5, 5, &g);
printgrid(&g);

return 0;
}


void initilgrid(grid* g)
{
    for (int i = 0; i < MAXGRID; i++) {
        for (int j = 0; j < MAXGRID; j++) {
            g->pixel[i][j] = ' ';
        }
    }
}


void linedraw(int x1, int y1, int x2, int y2, grid* g) {
    int dx = abs(x2 - x1);
    int sx = x1 < x2 ? 1 : -1;
    int dy = -abs(y2 - y1); // Notice dy is negative here
    int sy = y1 < y2 ? 1 : -1;
    int err = dx + dy, e2; // Initialize error term

    while (true) { // Loop until break
        if (x1 >= 0 && x1 < MAXGRID && y1 >= 0 && y1 < MAXGRID) {
            g->pixel[y1][x1] = '*'; // Mark the pixel
        }
        if (x1 == x2 && y1 == y2) break; // Break out of the loop once the end is reached
        e2 = 2 * err;
        if (e2 >= dy) { // Move in x-direction
            err += dy;
            x1 += sx;
        }
        if (e2 <= dx) { // Move in y-direction, note dx is positive, dy is negative
            err += dx;
            y1 += sy;
        }
    }
}


void printgrid(grid* g){

for (int i = 0; i < MAXGRID; i++) {
    for (int j = 0; j < MAXGRID; j++) {
        printf("%c", g->pixel[i][j]);
    }
    printf("\n");
}

}









// void linedraw(double x1, double y1, double x2, double y2, grid* g){
// // calculate slope: 
// double dx = x2 - x1;
// double dy = y2 - y1;
// // if x is negative: 
// if (x1 < 0) {
//     dx = -dx;
// }
// // if y is negative:
// if (y1 < 0) {
//     dy = -dy;
// }

// double slope = dy / dx;
// double error = 0.5;

// // if dx > dy:

// if (dx > dy)
// {
//     while (x1 < x2) {
//         g->pixel[(int)x1][(int)y1] = '*';
//         //increment x;
//         x1++;
//         error += slope;
//         if (error >= 0.5) {
//             y1++;
//         }
//     error = 1 - error;

//     }  

// }

// // if dx < dy:
// if (dx < dy) 
// {

// while (y1 < y2) {
//     g->pixel[(int)x1][(int)y1] = '*';
//     // increment y;
//     y1++;
//     error += slope;
//     if (error >= 0.5) {
//         x1++;
//     }
//     error = 1 - error;
// }

// }

// }

