#include <bits/stdc++.h>
#include <cstddef>
#include <utility>

/*18.1

18.1-1 we could potentially have nodes of size 0
18.1-2 t = 2 and t = 3
18.1-3 ->
    3
12      45

18.1-4.
suppose there are 2t-1 keys in everynode
how many nodes there are if each has 2t children
Sum i=0 -> h (2t)^i
(2t)^(h+1) - 1/ 2t - 1 nodes.
times 2t - 1 we have (2t)^(h+1) keys

18.1-5 i know its a 234 because of claudson, i am too lazy to 
do this rn 

*/



struct bnode{
    uint size;
    bool leaf;
    std::vector<int> keys;
    std::vector<bnode*> pointers;
};

struct btree{
    bnode* root;
    uint size;
    uint t;
    //etc

    btree(uint min_degree){
        root = new bnode;
        root->size = 0;
        root->leaf = true;
        size = 0;
        t = min_degree;
    }

    std::pair<bnode*,int> search(bnode* x, int k);
    void split_child(bnode *x, int i);
    void insert(int k);
    void inset_nonfull(bnode* r, int k);
};


std::pair<bnode*,int> bsearch(bnode* p,int x){
    bnode* ptr = p;
    while(ptr!=nullptr){
        int i;
        for(i = 0; i < ptr->keys.size(); i++){
            if(x==ptr->keys.at(i)){
                return std::make_pair(ptr,i);
            }
            if(x < ptr->keys.at(i)) break;
        }
        ptr = ptr->pointers.at(i);
    }

    return std::make_pair(nullptr,-1);
}

std::pair<bnode*,int> btree::search(bnode* x, int k){
    int i = 0;
    while(i < x->size && k > x->keys.at(i)){
        i++;
    }

    if(i < x->size && k == x->keys.at(i)){
        return std::make_pair(x, i);
    }

    else if(x->leaf) return std::make_pair(nullptr,-1);

    else{
        //DISKREAD(X,Ci)
        return search(x->pointers.at(i),k);
    }
}

/*not really needed*/


void btree::split_child(bnode* x, int i){
    bnode* z = new bnode;
    bnode* y = x->pointers.at(i);
    z->leaf = y->leaf;
    z->size = t-1;

    for(int j = 0; j < t-1; j++){
        z->keys.push_back(y->keys.at(t + j));
    }
    if(!y->leaf){
        for(int j = 0; j < t; j++){
            z->pointers.push_back(y->pointers.at(j + t));
        }
    }

    y->size = t - 1;
    y->keys.resize(t-1);
    y->pointers.resize(t);
    
    x->pointers.push_back(nullptr);
    for(int j = x->size; j > i; j--){
        x->pointers.at(j+1) = x->pointers.at(j);
    }
    x->pointers.at(i+1) = z;

    x->keys.push_back(NULL);
    for(int j = x->size - 2; j >= i; j--){
        x->keys.at(j+1) = x->keys.at(j);
    }
    x->keys.at(i) = y->keys.at(t-1);
    x->size++;

    return; /*i think i can do better than this, it's unnecessairly complicated*/
}


/*the same, but without x->n*/
void my_split(bnode* x, int i, int t){
    bnode* y = x->pointers.at(i);
    bnode* z = new bnode;
    z->leaf = y->leaf;

    z->size = t-1;
    for(int j = t; j < 2*t - 1; j++){
        z->keys.push_back(y->keys.at(j));
    }

    if(!z->leaf){
        for(int j = t; j < 2*t; j++){
            z->pointers.push_back(y->pointers.at(j));
        }
    }

    x->pointers.push_back(nullptr);
    for(int j = x->pointers.size() - 2; j > i; j--){
        x->pointers.at(j+1) = x->pointers.at(j);
    }
    x->pointers.at(i+1) = z;

    x->keys.push_back(NULL);
    for(int j = x->keys.size() - 2; j >= i; j--){
        x->keys.at(j+1) = x->keys.at(j);
    }
    x->keys.at(i) = y->keys.at(t-1);
    y->keys.resize(t-1);

    //disk write y
    //disk write z
    //disk write x
}

void btree::insert(int k){
    bnode* r = root;
    if(r->keys.size() == 2*t - 1){
        bnode* s = new bnode;
        root = s;
        s->leaf = false;
        s->size = 0;
        s->pointers.push_back(r);
        split_child(s,0);
    }
    inset_nonfull(root,k);
}

void btree::inset_nonfull(bnode* x, int k){
    int i = x->size - 1;
    if(x->leaf){
        x->keys.push_back(NULL);
        while(i >= 0 && k < x->keys.at(i)){
            x->keys.at(i+1) = x->keys.at(i);
            i--;
        }
        x->keys.at(i+1) = k;
        x->size++;
        //disk write x
        return;
    }
    else{
        while(i >= 0 && k < x->keys.at(i)){
            i--;
        }
        i++;
        //disk read ci
        if(x->pointers.at(i)->size == 2*t - 1){
            split_child(x,i);
            if(k>x->keys.at(i)){
                i++;
            }
        }
        inset_nonfull(x->pointers.at(i),k);
    }

}