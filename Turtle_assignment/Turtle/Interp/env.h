#include <stdio.h>
#include <stdlib.h>


#define BASE_KEY 'A'
#define MAX_KEY 'Z'
#define KEYS (MAX_KEY - BASE_KEY + 1)

#define KEY(x) (x - 'A')

typedef struct env {
  double mapping[KEYS]; // union of letters, doubles or words. 
    // switch double here for value structure. 
  int assigned[KEYS];
} env_t;

void check_key(char key) {
  if (key < BASE_KEY || key >= MAX_KEY) {
    fprintf(stderr, "Unrecognised key '%c'", key);
    exit(1);
  }
}

double get_key(env_t* e, char key) {
  check_key(key);

  if (!e->assigned[KEY(key)]) {
    fprintf(stderr, "Unassigned key '%c'", key);
    exit(1);
  }

  return e->mapping[KEY(key)];
}

void set_key(env_t* e, char key, double d) {
  check_key(key);

  e->assigned[KEY(key)] = 1;
  e->mapping[KEY(key)] = d;
  
}

void init_env(env_t* e) {
  for (char i = BASE_KEY; i <= MAX_KEY; i++) {
    e->assigned[KEY(i)] = 0;
  }
}
