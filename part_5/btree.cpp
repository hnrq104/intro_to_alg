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

std::pair<bnode*,int> bsearch(int x, bnode* p){
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

std::pair<bnode*,int> b_tree_search(bnode* x, int k){
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
        return b_tree_search(x->pointers.at(i),k);
    }
}

bnode* b_tree_create(void){
    bnode* ptr = new bnode;
    
}



