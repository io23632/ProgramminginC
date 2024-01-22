#include <stdio.h>

#define MAXGRID 20

typedef struct grid{
    char pixel[MAXGRID][MAXGRID]
}grid;

void linedraw(double x1, double y1, double x2, double y2, grid g);
void initilgrid(grid pixel);




int main(int argc, char* argv[])
{

FILE* file = freopen(argv[2], "w", stdout);
if (file == NULL) {
    perror("Error opening output file ");
    return 1;
}

grid g;

initilgrid(g);

linedraw(0, 0, 8, 5, g);

return 0;
}


void initilgrid(grid g)
{
    for (int i = 0; i < MAXGRID; i++) {
        for (int j = 0; j < MAXGRID; j++) {
            g.pixel[i][j] = ' ';
        }
        printf("\n");
    }
}

void linedraw(double x1, double y1, double x2, double y2, grid g){
// calculate slope: 
double dx = x2 - x1;
double dy = y2 - y1;
// if x is negative: 
if (x1 < 0) {
    dx = -dx;
}
// if y is negative:
if (y1 < 0) {
    dy = -dy;
}

double slope = dy / dx;
double error = 0.5;

// if dx > dy:

if (dx > dy)
{
    while (x1 < x2) {
        g.pixel[(int)x1][(int)y1] = '*';
        //increment x;
        x1++;
        error += slope;
        if (error >= 0.5) {
            y1++;
        }
    error = 1 - error;

    }  

}

// if dx < dy:
if (dx < dy) 
{

while (y1 < y2) {
    g.pixel[(int)x1][(int)y1] = '*';
    // increment y;
    y1++;
    error += slope;
    if (error >= 0.5) {
        x1++;
    }
    error = 1 - error;
}

}







}
