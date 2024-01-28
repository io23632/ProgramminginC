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
    env e;
    stack* stck = init_stack();
    grid g;
    TurtleState state = {26, 17, 90, 'W'};
    initilgrid(&g);
    init_env(&e);
    
    // if the input is: ./interp.c <inputfile.ttl> <outputfile.txt>: print results to text file
    if (argc == 3) {
        freopen(argv[2], "w", stdout);
        parsePROG(&p, &head);
        interp(head, &state, &e, &g, stck);
        //writetoFile(&g, argv[2]);
        fclose(stdout);
    }
    // if the input is: ./interp.c <inputfile.ttl>: print results to screen
    else if (argc == 2) {
        parsePROG(&p, &head);
        interp(head, &state, &e, &g, stck);
    }
    freeINSLST(head);
    free(stck);
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

void interp(INSLST* inslst, TurtleState* state, env* e, grid* g, stack* stck) {

    while (inslst != NULL) {
        switch (inslst->type) {
            case INS_FWD:
                go_fwd(state, inslst->ins.fwd, g, e);
                break;
            case INS_RGT:
                turn_rgt(state, inslst->ins.rgt, e);
                break;
            case INS_COL:
                set_col(state, inslst->ins.col);
                break;
            case INS_LOOP:
                interp_loop(&inslst->ins.loop, state, e, g, stck);
                break;
            case INS_SET:
                interp_set_env(e, &inslst->ins.set, stck);
                break;
            default:
                fprintf(stderr, "Unrecognized instruction type\n");
                break;
        }
        inslst = inslst->next;
        //g->pixel[(int)state.y][(int)state.x] = 'O';
        //printgrid(g);
          
    }
}

FWD parseFWD(prog* p)
{
    FWD fwd_ins;
    p->current_count++;

    // if there is a number following the FORWARD Instruction:
    if (isNUMBER(p->input[p->current_count])) {
        fwd_ins.type = NUMBER;
        if (sscanf(p->input[p->current_count], "%lf", &fwd_ins.varnum.number) != 1) {
            fprintf(stderr, "Error: Invalid number format after FORWARD\n");
            exit(1);
        }
        p->current_count++;
        return fwd_ins;
    }


    // if there is a variable following the FORWARD Instruction:
    else if (isVARIABLE(p->input[p->current_count])) {
        fwd_ins.type = VARIABLE;
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
    p->current_count++;

    // if there is a number following the RIGTH Instruction:
    if (isNUMBER(p->input[p->current_count])) {
        rgt_ins.type = NUMBER;
        if (sscanf(p->input[p->current_count], "%lf", &rgt_ins.varnum.number) != 1) {
            fprintf(stderr, "Expected a valid token number after RIGHT\n");
            exit(1);
        }
        p->current_count++;
        return rgt_ins;
    }

    // if there is a variable following the RIGTH Instruction:
    else if (isVARIABLE(p->input[p->current_count])) {
        rgt_ins.type = VARIABLE;
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

void interp_set_env(env* e, SET* s, stack* stck)
{
double result = evaluate_postfix(e, s, stck);
setkey_number(e, s->letter, result);
}

void interp_loop(LOOP* loop, TurtleState* state, env* e, grid* g, stack* stck) 
{
for (int i = 0; i < loop->loop_set->list_count; i++) {
    ITEM current_item = loop->loop_set->item_data[i];
    if (current_item.type == NUMBER) {
        setkey_number(e, loop->loop_variable, loop->loop_set->item_data[i].items.varnum.number);
        printf("%lf\n", loop->loop_set->item_data[i].items.varnum.number);
    }

    else if (current_item.type == Word) {
        char colour = set_col(state, loop->loop_body->ins.col.COL_postfix.word.str);
        printf("%c\n", colour);
    }


    else if (current_item.type == VARIABLE) {
        char varkey = loop->loop_set->item_data[i].items.varnum.variable;
        double number = getkey_number(e, varkey);
        setkey_number(e, loop->loop_variable, number);
    }

    interp(loop->loop_body, state, e, g, stck);
    
    // Tweek this: items.varnum.number = atom, where atom is a struct, with 1 field which has a type, and a union of variables and values. 
}

}

// Write a evaluater: needs to calculate the value of the postfix expression. recursive 
// atomic expressions can exist as variables, numbers, letters of words. described via a strucuture, which includes a type
// in the environment any atomic expression has a value. 
// two unions, one is called value : number letter or word 
//              atom: variable or a value 
// environment stores values, atom can be turned into a value as long as you have a envirnment. 
// S

void parsePOSTFIX(prog* p, SET* set) {

    while (strcmp(p->input[p->current_count], ")") != 0) {
        if (set->postfix_count >= MAXTOKENSIZE) {
            fprintf(stderr, "Postfix expression is too large\n");
            exit(1);
        }

        PFix* currentPFix = &set->postfix[set->postfix_count];

        if (isNUMBER(p->input[p->current_count])) {
            currentPFix->type = NUMBER;
            if (sscanf(p->input[p->current_count], "%lf", &currentPFix->precurse.varnum.number) != 1) {
                fprintf(stderr, "Invalid number in postfix expression\n");
                exit(1);
            }
        }

        else if (isVARIABLE(p->input[p->current_count])) {
            currentPFix->type = VARIABLE;
            currentPFix->precurse.varnum.variable = p->input[p->current_count][1];
    
        }
        else if (isOperation(p->input[p->current_count])) {
            currentPFix->type = OPERATION;
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

double evaluate_postfix(env* e, SET* set, stack* stck) {

    for (int i = 0; i < set->postfix_count; i++) {
        PFix* currentPFix = &set->postfix[i];

        if (currentPFix->type == NUMBER) {
            stack_push(stck, currentPFix->precurse.varnum.number);
            //printf("%lf\n", currentPFix->precurse.varnum.number);
        }
        else if (currentPFix->type == VARIABLE) {
            char varKey = currentPFix->precurse.varnum.variable;
            stack_push(stck, getkey_number(e, varKey));
            //printf("varKEY is: %c\n", varKey);
        }
        else if (currentPFix->type == OPERATION) {
            if (stck->size < 2) {
                fprintf(stderr, "Not enough operands for operation\n");
                exit(1);
            }
            double b = stack_pop(stck);
            //printf("b is: %lf\n", b);
            double a = stack_pop(stck);
            //printf("a is: %lf\n", a);
            double result = 0;
            //printf("%c\n", currentPFix->precurse.symbol);

            switch (currentPFix->precurse.symbol) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = a / b; break;
                default:
                    fprintf(stderr, "Unrecognised operation: %c\n", currentPFix->precurse.symbol);
                    exit(1);
            }
            stack_push(stck, result);
            //printf("result is %lf\n", result);
        }
        
    }

    if (stck->size != 1) {
        fprintf(stderr, "Error in postfix evaluation\n");
        exit(1);
    }
    double finalResult = stack_pop(stck);
    return finalResult;
}

LOOP parseLOOP(prog* p)
{

    LOOP loop;
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
    currentList->type = NUMBER;
    if (sscanf(p->input[p->current_count], "%lf", &currentList->items.varnum.number) != 1) {
        fprintf(stderr, "Invalid number in list");
        exit(1);
    }
}

// if is variable:

else if (isVARIABLE(p->input[p->current_count])) {
    currentList->type = VARIABLE;
    currentList->items.varnum.variable = p->input[p->current_count][0];
}

else {
    currentList->type = Word;
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

void go_fwd(TurtleState* state, FWD fwd_interp, grid* g, env* e)
{

    // if (is number)
    double radianANgle = state->angle * M_PI / 180.0;
    NUM x1 = state->x;
    NUM y1 = state->y;
    if (fwd_interp.type == NUMBER) 
    {
    double distance = fwd_interp.varnum.number;
    NUM x2 = x1 + distance * round(cos(radianANgle));
    NUM y2 = y1 + distance * round(sin(radianANgle));
    linedraw(x1, y1, x2, y2, g, state->colour);
    state->x = x2;
    state->y = y2;
    }

    else if (fwd_interp.type == VARIABLE)
    {
        char varkey = fwd_interp.varnum.variable;
        double distance = getkey_number(e, varkey);
        NUM x2 = x1 + distance * round(cos(radianANgle));
        NUM y2 = y1 + distance * round(sin(radianANgle));
        linedraw(x1, y1, x2, y2, g, state->colour);
        state->x = x2;
        state->y = y2;
    }

    printgrid(g);
    
}

void turn_rgt(TurtleState* state, RGT rgt_ins, env* e) 
{
    if (rgt_ins.type == NUMBER) {
        state->angle = state->angle - rgt_ins.varnum.number;
    }
    else if (rgt_ins.type == VARIABLE) {
        char varkey = rgt_ins.varnum.variable;
        double angle = getkey_number(e, varkey);
        state->angle = state->angle - angle;
    }
}

stack* init_stack(void)
{
    stack* s = (stack*)malloc(sizeof(stack));
    if(s == NULL) {
        fprintf(stderr, "Memory allocation failure");
    }
    s->size = 0;
    return s;
}

void stack_push(stack* s, NUM number)
{
    if (s->size >= MAXTOKENSIZE) {
        fprintf(stderr, "Stack is full"); 
        exit(1);   
    }

    s->arr[s->size] = number;
    s->size++;

}

double stack_pop(stack* s) {
    if (s == NULL || s->size <= 0) {
        fprintf(stderr, "Stack underflow\n");
        exit(1);
    }
    s->size--;
    return s->arr[s->size];
}

void initilgrid(grid* g)
{
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            g->pixel[j][i] = ' ';
        }
    }
}

bool inbounds(NUM x1, NUM y1)
{
    if (x1 < 0) {
        x1 = 0;
    }
    if (y1 < 0) {
        y1 = 0;
    }
    if (x1 >= GRID_WIDTH) {
        x1 = GRID_WIDTH - 1;
    }
    if (y1 >= GRID_HEIGHT) {
        y1 = GRID_HEIGHT - 1;
    }
    return true;
}

void linedraw(int x1, int y1, int x2, int y2, grid* g, char colour)
{
    NUM dx = abs(x2 - x1);
    NUM dy = -abs(y2 - y1);
    int sx;
    int sy;

    if (x1 <= x2) {
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

        if ((inbounds(x1, y1))) 
        {
            g->pixel[x1][y1] = colour;
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

        else {
            fprintf(stderr, "Co-ordinates out of bound");
            exit(1);
        }

    }

}

void printgrid(grid* g)
{
    neillclrscrn();
    neillcursorhome();
    for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
        printf("%c", g->pixel[j][i]);
        
    }
    printf("\n");
}
neillbusywait(0.5); 
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

    else {
        fprintf(stderr, "Colour not recognised\n");
        exit(1);
    }
}

// initiliase the environment:
void init_env(env* e) 
{
for (char i = BASE_KEY; i <= MAX_KEY; i++) {
    e->assigned[KEY(i)] = 0;
}
e->assigned_keycount = 0;
}

void check_key(env* e, char key)
{
    if (key < BASE_KEY || key >= MAX_KEY) {
        fprintf(stderr, "Unrecognised key %c, ", key);
        exit(1);
    }
    if (e->assigned_keycount >= MAX_KEY) {
        fprintf(stderr, "All letters have assigned variables");
        exit(1);
    }
}

double getkey_number(env* e, char key) {
  check_key(e, key);

  if (!e->assigned[KEY(key)]) {
    fprintf(stderr, "Unassigned key '%c'", key);
    exit(1);
  }

  return e->env_list.num_mapping[KEY(key)];
}

LTR getkey_letter(env* e, char key) {
  check_key(e, key);

  if (!e->assigned[KEY(key)]) {
    fprintf(stderr, "Unassigned key '%c'", key);
    exit(1);
  }

  return e->env_list.ltr_mapping[KEY(key)];
}

WORD getkey_word(env* e, char key) {
  check_key(e, key);

  if (!e->assigned[KEY(key)]) {
    fprintf(stderr, "Unassigned key '%c'", key);
    exit(1);
  }

  return e->env_list.word_mapping[KEY(key)];
}

void setkey_number(env* e, char key, double d) {
    
    check_key(e, key);

    e->assigned[KEY(key)] = 1;
    e->env_list.num_mapping[KEY(key)] = d;
    
}

// for loop
void setkey_letter(env* e, char key, LTR l)
{
    check_key(e, key);

    e->assigned[KEY(key)] = e->assigned_keycount;
    e->env_list.ltr_mapping[KEY(key)] = l;
    e->assigned_keycount++;
}
// for loop 
void setkey_word(env* e, char key, WORD word)
{
    check_key(e, key);

    e->assigned[KEY(key)] = e->assigned_keycount;
    e->env_list.word_mapping[KEY(key)] = word;
    e->assigned_keycount++;
}


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










// void interp_set(stack* s, SET* set)
// {
    

//     for (int i = 0 ; i < set->postfix_count; i++) {
//         PFix* currentPFix = &set->postfix[i];

//         if (currentPFix->type == NUMBER) {
//             stack_push(s, currentPFix->precurse.varnum.number);
//             printf("%lf\n", currentPFix->precurse.varnum.number);
//         }
        

        
//     }

// }

