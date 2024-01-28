#include <stdio.h>
#include <stdlib.h>


#pragma once 
// SET A ( 2 )
// SET B ( $A 1 + )
// SET C ( $CB 2* )
// LOOP A OVER { 1 2 3 4 5 6 7 8 }
// LOOP B OVER  { "BLACK" "RED" "GREEN" }

#define BASE_KEY 'A'
#define MAX_KEY 'Z'
#define KEY_RANGE (MAX_KEY - BASE_KEY + 1)
#define KEY(x) (x - 'A')

typedef struct env{
    union {
        double num_mapping[KEY_RANGE]; // assign numbers (in double form to the letters in the KEY RANGE)
        LTR ltr_mapping[KEY_RANGE]; // assign char i.e. variables e.g. $B to the letters in KEY RANGE, where LTR is typedef char LTR
        WORD word_mapping[KEY_RANGE]; // assign words to the letters in the key range 
        Op op_mapping[KEY_RANGE]; // assign operations to letters in the key range
    }env_list;
    int assigned[KEY_RANGE];
    int assigned_keycount;
}env;

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
  check_key(key);

  if (!e->assigned[KEY(key)]) {
    fprintf(stderr, "Unassigned key '%c'", key);
    exit(1);
  }

  return e->env_list.num_mapping[KEY(key)];
}

LTR getkey_letter(env* e, char key) {
  check_key(key);

  if (!e->assigned[KEY(key)]) {
    fprintf(stderr, "Unassigned key '%c'", key);
    exit(1);
  }

  return e->env_list.ltr_mapping[KEY(key)];
}

WORD getkey_word(env* e, char key) {
  check_key(key);

  if (!e->assigned[KEY(key)]) {
    fprintf(stderr, "Unassigned key '%c'", key);
    exit(1);
  }

  return e->env_list.word_mapping[KEY(key)];
}

Op getkey_(env* e, char key) {
  check_key(key);

  if (!e->assigned[KEY(key)]) {
    fprintf(stderr, "Unassigned key '%c'", key);
    exit(1);
  }

  return e->env_list.op_mapping[KEY(key)];
}

void setkey_number(env* e, char key, double d) {
    
    check_key(key);

    e->assigned[KEY(key)] = e->assigned_keycount;
    e->env_list.num_mapping[KEY(key)] = d;
    e->assigned_keycount++;
}

void setkey_letter(env* e, char key, LTR l)
{
    check_key(key);

    e->assigned[KEY(key)] = e->assigned_keycount;
    e->env_list.ltr_mapping[KEY(key)] = l;
    e->assigned_keycount++;
}

void setkey_word(env* e, char key, WORD word)
{
    check_key(key);

    e->assigned[KEY(key)] = e->assigned_keycount;
    e->env_list.word_mapping[KEY(key)] = word;
    e->assigned_keycount++;
}

void setkey_Op(env* e, char key, Op operation)
{
    check_key(key);


    e->assigned[KEY(key)] = e->assigned_keycount;
    e->env_list.op_mapping[KEY(key)] = operation;
    e->assigned_keycount++;
}