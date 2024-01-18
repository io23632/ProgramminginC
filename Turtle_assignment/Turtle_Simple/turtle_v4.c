#include "turtle.h"


int main (int argc, char * argv[]) 
{
    testParsePROG_ValidInput();
    test();

if (argc < 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return 1;
}

FILE* file = fopen(argv[1], "r");
if (file == NULL) {
    fprintf(stderr, "Error opening file");
}

prog* p = (prog*)malloc(sizeof(prog));
p->current_count = 0;

if (p == NULL) {
    fprintf(stderr, "Memory allocation failure");
    fclose(file);
    return 1;
}

    int i = 0;
    while (fscanf(file, "%s", p->input[i]) == 1) {
        i++;
    }

parsePROG(p);
free(p);

return 0;
}

void parsePROG(prog* p)
{
    if (strcmp(p->input[p->current_count], "START") != 0) {
        fprintf(stderr, "Expected a START\n");
        exit(1);
    }
   
    else {
        p->current_count++;
        parseINSLST(p);
    }
   
}

void parseINSLST(prog* p) {

    while (strcmp(p->input[p->current_count], "END") != 0) {
        if (strcmp(p->input[p->current_count], "FORWARD") == 0) {
            parseFWD(p);
        }
        else if (strcmp(p->input[p->current_count], "RIGHT") == 0) {
            //parseRGT(p);
        }
        else if (strcmp(p->input[p->current_count], "COLOUR") == 0) {
            //parseCOL(p);
        }
        else if (strcmp(p->input[p->current_count], "SET") == 0) {
            //parseSET(p);
        }
        else {
            fprintf(stderr, "INVALID TOKEN / EXPECTED AN END\n");
            exit(1);
        }

        p->current_count++;
    }

    printf("Program Finished\n");
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
    for (int i = 0; i < str[i] != '\0'; i++) {
        if(!isupper(str[i])) {
            return false;
        }
    }
    return true;
}

void testParsePROG_ValidInput() {
    prog p;
    strcpy(p.input[0], "START");
    strcpy(p.input[1], "FORWARD 5");
    strcpy(p.input[2], "END");
    p.current_count = 0;

    parsePROG(&p);
    assert(p.current_count > 0); // Expect the count to advance
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
    assert(isOperation("-") == true);
    

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