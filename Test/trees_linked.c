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
bool _isin(dataframe* t, int d);

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

bool _isin(dataframe* t, int d)
{
    /*If tree is NULL (empty) return false*/
    if (t == NULL){
        return false;
    }

    /*t->i is the current node of the tree, so if d is the current node 
    then return true*/
    if (t->i == d){
        return true;
    }

    /*if however d is not the current note then either d is less than the current node, in which case
    go to the left of the tree (via t->left) and call the function again which will then look at the next 
    node (now the next node is the current one) and evaluate the condition above */


    if (d < t->i){
        return _isin(t->left, d);
    }

    /* else if d is bigger than the current node than the recurisve procerss repeats */
    
    else {
        return _isin(t->right, d);
    }

return false;
}

