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

// represent two different types of NODES: 
typedef enum NodeType
{
    CHAR_NODE,
    PAIR_NODE,
}NodeType;

typedef char CharValue;

typedef struct PairValue{
    Node* left;
    Node* right;
}PairValue;

// A node value can either be a PAIR VALUE or  CHAR VALUE 

typedef union NodeValue{
    CharValue value; // just character 'a' or 'b'
    PairValue pair; // will have left and right pointers to contain a value or node 
}NodeValue;

typedef struct Node
{
    NodeType type;
    NodeValue data;

}Node;


int main(void)
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