#include "turtle.h"

/*
GRAMMAR to parse:
<PROG> ::= "START" <INSLST>
<INSLST> ::= "END" | <INS> <INSLST>
<INS> ::= <FWD> | <RGT>
<FWD> ::= "FORWARD" <NUM>
<RGT> ::= "RIGHT" <NUM>
<NUM> ::= 10 or -17.99 etc.
*/

int main(int argc, char * argv[])
{

   if (argc < 2)
   {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]); 
    return 1;
   }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Error openining file");
    }

    prog* p = (prog*)malloc(sizeof(prog));
    if (p == NULL) {
        fprintf(stderr, "Memory allocation error");
        fclose(file);
        return 1;
    }

    Ts* turtle = (Ts*)malloc(sizeof(Ts));
    if (turtle == NULL) {
        printf("Memory allocation error");
        fclose(file);
        return 1;
    }

    turtle->x = 0;
    turtle->y = 0;
    turtle->direction = 0;

    int i = 0;
    while (fscanf(file, "%s", p->input[i]) == 1) {
        i++;
    }
    parsePROG(p, turtle);

    free(p);
    free(turtle);

return 0;
}


void parsePROG(prog* p, Ts* turtle)
{
    if (strcmp(p->input[p->current_count], "START") != 0) {
        fprintf(stderr, "Expected a START ");
        exit(1);
    }

    else {
        p->current_count++;
        parseINSLST(p, turtle);
    }
}


void parseINSLST(prog* p, Ts* turtle)
{

    if (strcmp(p->input[p->current_count], "END") == 0) {
        printf("\nPrograme Finished\n");
        exit(0);
    }

    else if (strcmp(p->input[p->current_count], "FORWARD") == 0)
    {
        parseFWD(p, turtle);
        parseINSLST(p, turtle);
    }

    else if (strcmp(p->input[p->current_count], "RIGHT") == 0)
    {
        parseRGT(p, turtle);
        parseINSLST(p, turtle);
    }
    
    else {
        fprintf(stderr, "INVALID TOKEN / EXPECTED A END\n");
        exit(1);
    }
}


FWD parseFWD(prog* p, Ts* turtle)
{
    FWD fwd_ins;

    fwd_ins.type = INS_FWD;
    p->current_count++;


    if (isNUMBER(p->input[p->current_count])) {
        if (sscanf(p->input[p->current_count], "%lf", &fwd_ins.number) == 1)
        //Interpreter Code:
        move_fwd(turtle, fwd_ins.number);       
        p->current_count++;
        return fwd_ins;
    }

    else {
        fprintf(stderr, "expexted a number after FORWARD\n");
        exit(1);

    }
}

RGT parseRGT(prog* p, Ts* turtle)
{
    
    RGT rgt_ins;
    rgt_ins.type = INS_RGT;
    p->current_count++;

    if (isNUMBER(p->input[p->current_count])) {
        if (sscanf(p->input[p->current_count], "%lf", &rgt_ins.number) == 1)

        //Interpreter Code
        move_rgt(turtle, (int)rgt_ins.number);

        p->current_count++;
        return rgt_ins;
    }

    else {
        fprintf(stderr, "Error: Expected a number after 'RIGHT'\n");
        exit(1);
    }
    
}

void move_fwd(Ts* turtle, NUM distance)
{
    switch (turtle->direction) {
        case 0: // move forwar from North:
        turtle->y += distance;
        print_W(distance);
        break;

        case 90:
        turtle->x += distance;
        print_W(distance);
        break;

        case 180:
        turtle->y -= distance;
        print_W(distance);
        break;

        case 270:
        turtle->x -= distance;
        print_W(distance);
        break;
    }

}

void move_rgt(Ts* turtle, int angle)
{
    turtle->direction = (turtle->direction + angle) % 360;
}

void print_W(int n)
{
    for (int i = 0; i < n; i++) {
        printf("W");
    }

}


bool isNUMBER(const char* str){

    double temp;
    return sscanf(str, "%lf", &temp) == 1;
}
