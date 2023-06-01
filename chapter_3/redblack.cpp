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

void left_rotate(redblack* &root,redblack* ptr){
    redblack* y = ptr->right;
    ptr->right = y->left;
    y->left = ptr;

    y->p = ptr->p;
    if(ptr->p == nullptr){
        root = y;
    }
    else if(ptr == ptr->p->left){
        ptr->p->left = y;
    }
    else{
        ptr->p->right = y;
    }

    ptr->p = y;
    
}

void right_rotate(redblack* &root, redblack* ptr){
    redblack* x = ptr->left;
    ptr->left = x->right;
    x->right = ptr;

    x->p = ptr->p;

    if(ptr->p == nullptr){
        root = x;
    }
    else if(ptr == ptr->p->left){
        ptr->p->left = x;
    }
    else{
        ptr->p->right = x;
    }

    ptr->p = x;
}

redblack::color col(redblack* ptr){
    if(ptr == nullptr){
        return redblack::BLACK;
    }
    return ptr->cor;

}


void rb_insert_fixup(redblack* &root, redblack* z){
    while(col(z->p) == redblack::RED){
        if(z->p == z->p->p->left){
            redblack* y = z->p->p->right;
            if(col(y) == redblack::RED){
                z->p->cor = redblack::BLACK;
                y->cor = redblack::BLACK;
                z->p->p->cor = redblack::RED;
                z = z->p->p;
            }

            else{
                if(z == z->p->right){
                    z = z->p;
                    left_rotate(root, z);
                }

                z->p->cor = redblack::BLACK;
                z->p->p->cor = redblack::RED;
                right_rotate(root,z->p->p);
            }

        }

        else{
            redblack* y = z->p->p->left;
            if(col(y) == redblack::RED){
                z->p->cor = redblack::BLACK;
                y->cor = redblack::BLACK;
                z->p->p->cor = redblack::RED;
                z = z->p->p;
            }

            else{
                if(z == z->p->left){
                    z = z->p;
                    right_rotate(root,z);
                }
                z->p->cor = redblack::BLACK;
                z->p->p->cor = redblack::RED;
                left_rotate(root,z->p->p);
            }
        }
    }

    root->cor = redblack::BLACK;
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
    z->left = nullptr;
    z->right = nullptr;

    rb_insert_fixup(root,z);
}


void rb_transplant(redblack* &root, redblack* u, redblack* v){
    if(u->p == nullptr){
        root = v;
    }
    else if(u == u->p->left){
        u->p->left = v;
    }
    else{
        u->p->right = v;
    }
    v->p = u->p;
}


int main(void){

    std::cout<<redblack::RED << std::endl;
      
    return 0;
}


