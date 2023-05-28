/*
1. Every node is either red or black.
2. The root is black.
3. Every leaf is black.
4. If a node is red, then both of its children are black.
5. For each node, all simple paths from the node to descendant leaves
contain the same number of black nodes.

As written by Moses.
*/

#include<bits/stdc++.h>
struct redblack{    
    enum color{RED, BLACK};
    
    redblack* p;
    int key;
    color cor;
    redblack* left;
    redblack* right;

    redblack(int k){
        p = nullptr;
        key = k;
        cor = RED;
        left = nullptr;
        right = nullptr;
    }
};

void left_rotate(redblack* &ptr){
    redblack* y = ptr->right;
    ptr->right = y->left;
    if(y->left != nullptr){
        y->left->p = ptr;
    }
    y->left = ptr;
    y->p = ptr->p;
    ptr->p = y;
    ptr = y;
}

void right_rotate(redblack* &ptr){
    redblack* x = ptr->left;
    ptr->left = x->right;
    if(x->right != nullptr){
        x->right->p = ptr;
    }
    x->right = ptr;
    x->p = ptr->p;
    ptr->p = x;
    ptr = x;
}

redblack::color col(redblack* ptr){
    if(ptr == nullptr){
        return redblack::BLACK;
    }
    return ptr->cor;

}

void rb_insert(redblack* &root, redblack* z){
    redblack* y = nullptr;
    redblack* x = root;
    while (x != nullptr){
        y = x;
        if(z->key < x->key){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }

    z->p = y;
    if(y == nullptr){
        root = z;
    }

    else if(z->key < y->key){
        y->left = z;
    }

    else{
        y->right = z;
    }
    
    z->cor = redblack::RED;

    //RB->INSERT FIXUP(T,Z)
}



int main(void){

    std::cout<<redblack::RED << std::endl;
      
    return 0;
}


