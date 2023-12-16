#include "../ADTs/General/general.c"

typedef struct dataframe{
    int i;
    struct dataframe* left;
    struct daraframe* right;
}dataframe;


typedef struct root{
    dataframe* root;
}root;

dataframe* _insert(dataframe* t, int d);

dataframe* _insert(dataframe* t, int d)
{
    if (t == NULL){
        dataframe* f = (dataframe*)calloc(1, sizeof(dataframe));
        f->i = d;
        f->left = NULL;
        f->right = NULL;
        return f;
    }

    if (d < t->i){
        t->left = _insert(t->left, d);
    }

    else if (d > t->right) {
        t->right = _insert(t->right, d);
    }

    return t;
}