#include <stdio.h>
#include <stdlib.h>

/*
GRAMMAR we are trying to parse:

NODE ::= <CHAR> | <PAIR>
CHAR ::= Any character that is not a '(' or ')'
PAIR ::= '(' <NODE> <NODE> ')'

example : a (b c)

*/

// represent two different types of NODES: 
typedef enum NodeType
{
    CHAR_NODE,
    PAIR_NODE,
}NodeType;

typedef char CharValue;
typedef char* ErrorValue;

typedef struct PairValue{
    Node* left;
    Node* right;
}PairValue;

// A node value can either be a PAIR VALUE or  CHAR VALUE 

typedef union NodeValue{
    CharValue value; // just character 'a' or 'b'
    PairValue pair; // will have left and right pointers to contain a value or node 
    ErrorValue error;
}NodeValue;

typedef struct Node
{
    NodeType type;
    NodeValue data;

}Node;


Node* parse_char(char c);


int main (void) 
{

    return 0;
}


Node* parse_char(char c)
{
Node* node = (Node*)malloc(sizeof(Node));
node->type = CHAR_NODE;
node->data.value = c;
return node;
}