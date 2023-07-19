#include <bits/stdc++.h>
#include <cstddef>
#include <utility>
#include <vector>

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
    bool delete_key(bnode* x,int k);
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

/*
18.2
18.2-1
draw
18.2-2
i don't think redundant calls are made will check
18.2-3
go furthest to the left.

predecessor:
closest ancestor youre part of the right branch
check in the node aswell
rightmost child of left branch

18.2-4
...
...

18.2-6
binary search takes will take log_2(t)
we will have in general search taking
log_2(t) * log_t(n) = (log t/ log 2)*(log n /log t)
but this is precisely log(n)

18.2-7 no idea
*/


/*18.3-2 don't think i will do it right*/

bool btree::delete_key(bnode* x, int k){
    int i = 0;
    bool found = false;
    /*try to find k in node*/
    for(int i = 0; i < x->keys.size(); i++){
        if(x->keys.at(i) == k){
            found = true;
            break;
        }
        if(x->keys.at(i) > k) break;
    }
    /*case 1 
    if k is in node x and x is a leaf, delete key k
    */
    if(found && x->leaf){
        x->keys.erase(x->keys.begin() + i);
        return true;
    }

    /*if k is in node x but is not a leaf*/
    if(found){
        if(x->pointers.at(i)->size >= t){
            bnode* pre = x->pointers.at(i);
            while(!pre->pointers.empty()){
                pre = pre->pointers.back();
            }
            int num = pre->keys.back();
            delete_key(x->pointers.at(i), num);
            x->keys.at(i) = num;
            //delete predecessor at this subtree
            //can find k' and delete it with a single pass,
            //but it's would involve rewriting delete func
            //exchange it with k
            return true;
        }


        if(x->pointers.at(i+1)->size >= t){
            bnode* pre = x->pointers.at(i+1);
            while(!pre->pointers.empty()){
                pre = pre->pointers.front();
            }
            int num = pre->keys.front();
            delete_key(x->pointers.at(i), num);
            x->keys.at(i) = num;
            //delete sucessor at this subtree
            //can find k' and delete it with a single pass,
            //but it's would involve rewriting delete func
            //exchange it with k
            return true;
        }

        else{
            //merge both nodes and remove recursevely from merged
            bnode* y = x->pointers.at(i);
            y->keys.push_back(k);
            bnode* z = x->pointers.at(i+1);
            for(int j = 0; j < z->keys.size(); j++){
                y->keys.push_back(z->keys.at(j));
                y->pointers.push_back(z->pointers.at(j));
            }
            y->pointers.push_back(z->pointers.back());
            delete z;
            x->keys.erase(x->keys.begin() + i);
            x->pointers.erase(x->pointers.begin() + i + 1);
            delete_key(y,k);

        }

    }

    /*case 3 i am too lazy :()*/    
    if(!found && x->leaf) return false; /*didn't find it*/

    /*not found but we are in an internal node*/
    if(x->pointers.at(i)->size > t-1){
        delete_key(x->pointers.at(i),k);
    }

    //else

    std::vector<bnode*> sib;
    bnode* big = nullptr;
    if(i != 0){
        sib.push_back(x->pointers.at(i-1));
        if(sib.back()->size != t-1){
            big = sib.back();
        }
    }
    if(i != t-2){
        sib.push_back(x->pointers.at(t-1));
        
    }

    



}
