#include <stdio.h>

/*
GRAMMAR we are trying to parse:

NODE ::= <CHAR> | <PAIR>
CHAR ::= Any character that is not a '(' or ')'
PAIR ::= '(' <NODE> <NODE> ')'

example : a (b c)

Our Node will look like this:                          
                         Node ->   PAIR | CHAR
                            Pair -> 
                                Left Node - >  
                                    Char - > 
                                        a
                                Rigt Node - > 
                                    Char - > 
                                        b
                        
*/

// NODE ::= <CHAR> | <PAIR> //

typedef enum nodetype{
    CHAR_NODE,
    PAIR_NODE,
}nodetype;

typedef struct Node Node;

typedef char CharValue; 

typedef struct PairValue{
    Node* left; 
    Node* right; 
}PairValue; 

typedef union NodeValue{
    PairValue pair;
    CharValue value;
}NodeValue;


struct Node{
    nodetype type;
    NodeValue data;
};

int main()
{

Node a; 
a.type = CHAR_NODE;
a.data.value = 'a';

Node b;
b.type = CHAR_NODE;
b.data.value = 'b';

Node p;
p.type = PAIR_NODE;
p.data.pair.left = &a;
p.data.pair.right = &b;

return 0;
}