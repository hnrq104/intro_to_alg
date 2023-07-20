#include <bits/stdc++.h>

//lazy evaluation it seems

struct node{
    int key; //key in node
    int deegre; // number of childre
    node* p; // parent node
    node* l; //left in double linked list
    node* r; //right in double linked list
    bool mark; // if it has lost a child since subjugation

};

struct heap{
    node* min; //tree containing min key
    int n; // number of trees
};

