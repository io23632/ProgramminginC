#include "interp.h"
#include "../neillsimplescreen.h"

int main(int argc, char *argv[]) {
    test();

    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s <inputfile> [<outputfile>]\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening input file");
        return 1;
    }
    
    prog p;
    p.current_count = 0;
   
    int i = 0;
    while (fscanf(file, "%s", p.input[i]) == 1)
    {
        i++;
    }

    INSLST* head = NULL;
    grid g;
    // if the input is: ./interp.c <inputfile.ttl> <outputfile.txt>: print results to text file
    if (argc == 3) {
        freopen(argv[2], "w", stdout);
        parsePROG(&p, &head);
        interp(head, &g);
        //writetoFile(&g, argv[2]);
        fclose(stdout);
    }
    // if the input is: ./interp.c <inputfile.ttl>: print results to screen
    else if (argc == 2) {
        parsePROG(&p, &head);
        interp(head, &g);
    }
    freeINSLST(head);
    
    return 0;
}

void parsePROG(prog* p, INSLST** head)
{
    if (strcmp(p->input[p->current_count], "START") != 0) {
        fprintf(stderr, "Expected a START\n");
        exit(1);
    }

    p->current_count++;
    parseINSLST(p, head);
    
}

void parseINSLST(prog* p, INSLST** inslst)
{

if (strcmp(p->input[p->current_count], "END") == 0 ) {
    return;
}

if (*inslst == NULL) {
    *inslst = (INSLST*)malloc(sizeof(INSLST));
    if (*inslst == NULL) {
        fprintf(stderr, "Memory allocation failure");
        exit(1);
    }
    (*inslst)->next = NULL;
}

if (strcmp(p->input[p->current_count], "FORWARD") == 0) {
    (*inslst)->type = INS_FWD;
    (*inslst)->ins.fwd = parseFWD(p);
    parseINSLST(p, &(*inslst)->next);

}

else if (strcmp(p->input[p->current_count], "RIGHT") == 0) {
    (*inslst)->type = INS_RGT;
    (*inslst)->ins.rgt = parseRGT(p);
    parseINSLST(p, &(*inslst)->next);
    
}

else if (strcmp(p->input[p->current_count], "COLOUR") == 0) {
    (*inslst)->type = INS_COL;
    (*inslst)->ins.col = parseCOL(p);
    parseINSLST(p, &(*inslst)->next);
}

else if (strcmp(p->input[p->current_count], "SET") == 0) {
    (*inslst)->type = INS_SET;
    (*inslst)->ins.set = parseSET(p);
    parseINSLST(p, &(*inslst)->next);
}

else if (strcmp(p->input[p->current_count], "LOOP") == 0) {
    (*inslst)->type = INS_LOOP;
    (*inslst)->ins.loop = parseLOOP(p);
    parseINSLST(p, &(*inslst)->next);
}
else {
    fprintf(stderr, "INVALID TOKEN in instruction list: %s\n", p->input[p->current_count]);
}


if (strcmp(p->input[p->current_count], "END") != 0) {
    p->current_count++;
    parseINSLST(p, &(*inslst)->next);
}

}

void interp(INSLST* inslst, grid* g) {

    TurtleState state = {25, 16, 90, true, 'W'};
    initilgrid(g);
    while (inslst != NULL) {
        switch (inslst->type) {
            case INS_FWD:
                go_fwd(&state, inslst->ins.fwd, g);
                break;
            case INS_RGT:
                turn_rgt(&state, inslst->ins.rgt);
                break;
            case INS_COL:
                set_col(&state, inslst->ins.col);
                break;
            // case INS_LOOP:
            //     interp_loop(&state, inslst->ins.loop);
            //     break;
            // case INS_SET:
            //     interp_set(&state, inslst->ins.set);
            //     break;
            default:
                fprintf(stderr, "Unrecognized instruction type\n");
                break;
        }
        inslst = inslst->next;
        //g.pixel[(int)state.y][(int)state.x] = 'O';
          
    }
    printgrid(g);
}

FWD parseFWD(prog* p)
{
    FWD fwd_ins;
    fwd_ins.type = INS_FWD;
    p->current_count++;

    // if there is a number following the FORWARD Instruction:
    if (isNUMBER(p->input[p->current_count])) {
        if (sscanf(p->input[p->current_count], "%lf", &fwd_ins.varnum.number) != 1) {
            fprintf(stderr, "Error: Invalid number format after FORWARD\n");
            exit(1);
        }
        p->current_count++;
        return fwd_ins;
    }


    // if there is a variable following the FORWARD Instruction:
    else if (isVARIABLE(p->input[p->current_count])) {
        fwd_ins.varnum.variable = p->input[p->current_count][1];
        p->current_count++;
        return fwd_ins;
    }

    else {
        fprintf(stderr, "expexted a number after FORWARD\n");
        exit(1);

    }
}

RGT parseRGT(prog* p)
{
    
    RGT rgt_ins;
    rgt_ins.type = INS_RGT;
    p->current_count++;

    // if there is a number following the RIGTH Instruction:
    if (isNUMBER(p->input[p->current_count])) {
        if (sscanf(p->input[p->current_count], "%lf", &rgt_ins.varnum.number) != 1) {
            fprintf(stderr, "Expected a valid token number after RIGHT\n");
            exit(1);
        }
        p->current_count++;
        return rgt_ins;
    }

    // if there is a variable following the RIGTH Instruction:
    else if (isVARIABLE(p->input[p->current_count])) {
        rgt_ins.varnum.variable = p->input[p->current_count][1];
        p->current_count++;
        return rgt_ins;
    }

    else {
        fprintf(stderr, "Error: Expected a variable or a number after 'RIGHT'\n");
        exit(1);
    }
    
}

COL parseCOL(prog* p)
{
    COL col_ins;
    col_ins.type = INS_COL;
    p->current_count++;

    // Check if it is a variable:
    if (isVARIABLE(p->input[p->current_count])) {
        col_ins.COL_postfix.variable = p->input[p->current_count][1];
        p->current_count++;
        return col_ins;
    }
    
    // Check if it is a word: // make into a function
    else {

        isWORD(p, col_ins.COL_postfix.word.str);
        
        p->current_count++;
        return col_ins;
    }

}

SET parseSET(prog* p)
{

SET set; 
set.type = INS_SET;
set.postfix_count = 0;
p->current_count++;

//parse the letter and move on to parsePFIX
if (isLetter(p->input[p->current_count])) {
    set.letter = p->input[p->current_count][0];
    p->current_count++;
    

    if(strcmp(p->input[p->current_count], "(") == 0) {
        p->current_count++;
        parsePOSTFIX(p, &set);
        
    }
    
    else {
        fprintf(stderr, "expected a ( after letter in SET statement\n");
        exit(1);
    }
}

else {
    fprintf(stderr, "Expected a letter in SET statement\n");
    exit(1);
}

return set;

}

void parsePOSTFIX(prog* p, SET* set) {

    while (strcmp(p->input[p->current_count], ")") != 0) {
        if (set->postfix_count >= MAXTOKENSIZE) {
            fprintf(stderr, "Postfix expression is too large\n");
            exit(1);
        }

        PFix* currentPFix = &set->postfix[set->postfix_count];

        if (isNUMBER(p->input[p->current_count])) {
            if (sscanf(p->input[p->current_count], "%lf", &currentPFix->precurse.varnum.number) != 1) {
                fprintf(stderr, "Invalid number in postfix expression\n");
                exit(1);
            }
        }

        else if (isVARIABLE(p->input[p->current_count])) {
            currentPFix->precurse.varnum.variable = p->input[p->current_count][1];
    
        }
        else if (isOperation(p->input[p->current_count])) {
            currentPFix->precurse.symbol = p->input[p->current_count][0];
            
        }
        else {
            fprintf(stderr, "Expected valid token for postfix expression at %s\n", p->input[p->current_count]);
            exit(1);
        }

        set->postfix_count++;
        p->current_count++;
    }

    p->current_count++; // Move past the closing parenthesis
}

LOOP parseLOOP(prog* p)
{

    LOOP loop;
    loop.type = INS_LOOP;
    loop.loop_body = NULL;
    loop.loop_set = NULL;
    p->current_count++;
    // check if there is a LTR preseant: 

    if (isLetter(p->input[p->current_count])) {
        loop.loop_variable = p->input[p->current_count][0];
        p->current_count++;
    }
    else {
        fprintf(stderr, "expected a letter after LOOP statement");
        exit(1);
    }

    // Check for the word over:
    if (strcmp(p->input[p->current_count], "OVER") != 0) {
        fprintf(stderr, "Expected a OVER statement at %s\n", p->input[p->current_count]);
        exit(1);
    }
    //p->current_count++;

    loop.loop_set = (LST*)malloc(sizeof(LST));
    if (loop.loop_set == NULL) {
        fprintf(stderr, "Memory allocation failure");
        exit(1);
    }

    *loop.loop_set = parseLST(p);

    INSLST* loop_body_head = NULL;

    while (strcmp(p->input[p->current_count], "END") != 0)
    {
        parseINSLST(p, &loop_body_head);
    }

    loop.loop_body = loop_body_head;

    p->current_count++;

    return loop;
}

LST parseLST(prog* p)
{
    LST list;
    list.list_count = 0;
    p->current_count++;

    
    if (strcmp(p->input[p->current_count], "{") != 0) {
        fprintf(stderr, "expected a { before list %s\n", p->input[p->current_count]);
        exit(1);
    }
    else {
        p->current_count++;
        parseITEM(p, &list);
    }

    return list;

}

void parseITEM(prog* p, LST* list)
{

while (strcmp(p->input[p->current_count], "}") != 0) {
    if (list->list_count >= MAXTOKENSIZE) {
        fprintf(stderr, "LIST size maximum reached");
        exit(1);
    }


ITEM* currentList = &list->item_data[list->list_count];

// if is Number: 
if (isNUMBER(p->input[p->current_count])) {
    if (sscanf(p->input[p->current_count], "%lf", &currentList->items.varnum.number) != 1) {
        fprintf(stderr, "Invalid number in list");
        exit(1);
    }
}

// if is variable:

else if (isVARIABLE(p->input[p->current_count])) {
    currentList->items.varnum.variable = p->input[p->current_count][0];
}

else {

    isWORD(p, list->item_data->items.word.str);
}

list->list_count++;
p->current_count++;

}

p->current_count++;
}

void isWORD(prog* p, char str[MAXTOKENSIZE])
{
    char* word = p->input[p->current_count];
    size_t word_length = strlen(word);

    if (word[0] == '\"' && word[word_length - 1] == '\"') {
        strncpy(str, word + 1, word_length - 2);
        str[word_length - 2] = '\0';
    }
    else {
        strncpy(str, word, MAXTOKENSIZE - 1);
        str[MAXTOKENSIZE - 1] = '\0';
    }
}

bool isOperation(const char* str)
{

if (((strcmp(str, "+") == 0)|| (strcmp(str, "-") == 0)||(strcmp(str, "*") == 0)|| (strcmp(str, "/") == 0))) {
    return true;
}
return false;

}

bool isNUMBER(const char* str){

    double temp;
    return sscanf(str, "%lf", &temp) == 1;
}

bool isVARIABLE(const char* str) {
    
if (str[0] == '$') {
    for (int i = 1; str[i] != '\0'; i++) {
        if (!isupper(str[i])) {
            return false;
        }
    }
    return true;
}
return false;
}

bool isLetter(const char* str)
{
    
    if (isVARIABLE(str)) {
        return false;
    }
    for (int i = 0; i < (str[i] != '\0'); i++) {
        if(!isupper(str[i])) {
            return false;
        }
    }
    return true;
}

void freeINSLST(INSLST* inslst) {
    
    while (inslst != NULL) {
        INSLST* temp = inslst;
        inslst = inslst->next; // Move to the next before freeing the current

        if (temp->type == INS_LOOP) {
            // Free the loop's list of items
            if (temp->ins.loop.loop_set != NULL) {
                free(temp->ins.loop.loop_set); // Free the dynamically allocated loop set
            }
            // Recursively free the loop body
            freeINSLST(temp->ins.loop.loop_body);
        }
        
        free(temp); // Free the current INSLST node
    }
}

void go_fwd(TurtleState* state, FWD fwd_interp, grid* g)
{
    // assuming the turtel state in initlised in main to be: 
    // Turtle state = { .x = 25, .y = 16, .angle = 90}

    double distance = round(fwd_interp.varnum.number);
    double radianANgle = state->angle * M_PI / 180.0;

    int x1 = state->x;
    int y1 = state->y;
    state->pen = true;

    int x2 = x1 + distance * cos(radianANgle);
    int y2 = y1 + distance * sin(radianANgle);

  
    // if (state->x < 0) {
    //     state->x = 0;
    // }
    // else if (state->x >= GRID_WIDTH){
    //     state->x = GRID_WIDTH -1;
    // }

    // if (state->y < 0) {
    //     state->y = 0;
    // }
    // else if (state->y >= GRID_HEIGHT) {
    //     state->y = GRID_HEIGHT - 1;
    // }

    if (x1 < 0) {
        x1 = 0;
    }
    else if (x1 >= GRID_WIDTH){
        x1 = GRID_WIDTH -1;
    }

    if (y1 < 0) {
        y1 = 0;
    }
    else if (y1 >= GRID_HEIGHT) {
        y1 = GRID_HEIGHT - 1;
    }
    
    state->x = x2;
    state->y = y2;
    linedraw(x1, y1, x2, y2, g, state->colour);
    // state->x = x2;
    // state->y = y2;
}

void turn_rgt(TurtleState* state, RGT rgt_ins) {

    state->angle = state->angle - rgt_ins.varnum.number;
}

void initilgrid(grid* g)
{
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            g->pixel[i][j] = ' ';
        }
    }
}

void linedraw(int x1, int y1, int x2, int y2, grid* g, char colour)
{
    int dx = abs(x2 - x1);
    int dy = -abs(y2 - y1);
    int sx;
    int sy;

    if (x1 < x2) {
        sx = 1;
    }
    else {
        sx = -1;
    }

    if (y1 < y2) {
        sy = 1;
    }
    else {
        sy = -1;
    }

    int P = dx + dy;
    int e2;

    while (true)
    {
        g->pixel[y1][x1] = colour;
        if (x1 == x2 && y1 == y2) {
            break;
        }

        e2 = P * 2;
        if (e2 >= dy) {
            P = P + dy;
            x1 = x1 + sx;
            
        }
        if (e2 <= dx) {
            P = P + dx;
            y1 = y1 + sy;
            
        }

    }

}

void printgrid(grid* g)
{
    for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
        printf("%c", g->pixel[i][j]);
    }
    printf("\n");
}

}

void set_col(TurtleState* state, COL col_interp)
{
    // create a enum instead
    if ((strcmp(col_interp.COL_postfix.word.str, "BLACK") == 0)) {
        state->colour = 'K';
    }
    else if ((strcmp(col_interp.COL_postfix.word.str, "RED") == 0)) {
        state->colour = 'R';
    }
    else if ((strcmp(col_interp.COL_postfix.word.str, "GREEN") == 0)) {
        state->colour = 'G';
    }
    else if ((strcmp(col_interp.COL_postfix.word.str, "YELLOW") == 0)) {
        state->colour = 'Y';
    }
     else if ((strcmp(col_interp.COL_postfix.word.str, "BLUE") == 0)) {
        state->colour = 'B';
    }
     else if ((strcmp(col_interp.COL_postfix.word.str, "MAGENTA") == 0)) {
        state->colour = 'M';
    }
    else if ((strcmp(col_interp.COL_postfix.word.str, "CYAN") == 0)) {
        state->colour = 'C';
    }
    else if ((strcmp(col_interp.COL_postfix.word.str, "WHITE") == 0)) {
        state->colour = 'W';
    }
}


// void writetoFile(grid* g, const char* filename) {
//     // open file in write functions 
//     FILE* file = fopen(filename, "w");

//     if(file == NULL) {
//         fprintf(stderr, "Error opening file\n");
//     }

//     for (int i = 0; i < GRID_HEIGHT; i++) {
//         for (int j = 0; j < GRID_WIDTH; j++) {
//             fputc(g->pixel[i][j], file);
//         }
    
//     }

// }


// void printgrid(grid* g)
// {
   
//     neillclrscrn();
//     neillcursorhome();
//     neillbgcol(black);
//     for (int i = 0; i < GRID_HEIGHT; i++) {
//         for (int j = 0; j < GRID_WIDTH; j++) {
            
//             switch (g->pixel[i][j]) {
//                 case 'K': neillfgcol(black);
//                 break;
//                 case 'R': neillfgcol(red); break;
//                 case 'G': neillfgcol(green); break;
//                 case 'Y': neillfgcol(yellow); break;
//                 case 'B': neillfgcol(blue); break;
//                 case 'M': neillfgcol(magenta); break;
//                 case 'C': neillfgcol(cyan); break;
//                 case 'W': neillfgcol(white); break;
//                 default: neillreset(); break; 
//             }

            
//             printf("%c", g->pixel[i][j]);

            
//             neillreset();
//         }
//         printf("\n");
//     }

    
//     neillbusywait(1.0);  
// }

void test(void) 
{

    
    assert(isNUMBER("10") == true);
    assert(isNUMBER("17.9987") == true);

    assert(isVARIABLE("$A") == true);
    assert(isVARIABLE("A") == false);
    assert(isVARIABLE("$a") == false);
    assert(isVARIABLE("$Z") == true);

    assert(isOperation("+") == true);
    assert(isOperation("/") == true);
    assert(isOperation("*") == true);
    assert(isLetter("A") == true);
    assert(isLetter("a") == false); 
    assert(isLetter("B") == true);
    assert(isLetter("b") == false);
    assert(isLetter("Y") == true);
    assert(isLetter("y") == false);
    assert(isLetter("U") == true);
    assert(isLetter("u") == false);
    assert(isLetter("$A") == false);

}
