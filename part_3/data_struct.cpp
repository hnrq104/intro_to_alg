/*
14.1
*/

#include<bits/stdc++.h>

enum cor{
    BLACK,
    RED
};

struct fruta{

    fruta* left;
    fruta* right;
    fruta* p;

    cor c;
    int key;
    int size;
};

int size(fruta* ptr){
    if(ptr == nullptr) return 0;
    else return ptr->size;
}

fruta* os_select(fruta* x, int i){
    int r = size(x->left);
    if(r == i){
        return x;
    }

    if(i < r){
        return os_select(x->left, i);
    }

    else{
        return os_select(x->right, i - r);
    }
}

int os_rank(fruta* x){
    int r = size(x->left) + 1;
    fruta* y = x;
    while(y->p != nullptr){
        if(y == y->p->right){
            r = r + size(y->p->left) + 1;
        }
        y = y->p;
    }
    return r;
}

//for insertion and deletion
//add one to everyone in the path of insertion
//take one out of everyone in the path of deletion
//rotations swap sizes

fruta* non_recursive_select(fruta *root, int i){
    int k = i;
    fruta* x = root;
    while(x!=nullptr){ //just so if its wrong it breaks
        int r = size(x->left) + 1;
        if(r == k){
            return x;
        }

        if(k < r){
            x = x->left;
        }

        else{
            k = k - r;
            x = x->right;
        }
    }
}

int os_key_rank(fruta* x, int key){
    if(x->key == key){
        return size(x->left) + 1;
    }

    if(x->key < key){
        return os_key_rank(x->left,key);
    } 

    else{
        return os_key_rank(x->right,key) + x->size + 1;
    }
}

void rb_enumerate(fruta* x, int a, int b){
    if(x == nullptr) return;

    if(x->key >= a && x->key <= b){
        std::cout << x->key << std::endl;
    }

    if(x->key >= a){
        rb_enumerate(x->left,a,b);
    }

    if(x->key <= b){
        rb_enumerate(x->right,a,b);
    }
}


//14.3-1
//write pseudocode for left rotate that operates and mantain max in O(1)

struct interval{
    interval* p;
    interval* left;
    interval* right;
    int low;
    int high;
    int max;
};

int max(interval* n, interval* m){
    int number = INT32_MIN;

    if(n !=nullptr) number = n->max;
    
    if(m !=nullptr){
        if(m->max > number){
            number = m->max;
        }
    }
    return number;
}

void left_rotate(interval* tree){
    interval* r = tree->right;
    tree->right = r->left;
    if(r->left != nullptr){
        r->left->p = tree;
    }
    r->left = tree;
    r->p = tree->p;
    if(tree->p != nullptr){
        if(tree->low <= tree->p->low){
            tree->p->left = r;
        }
        else{
            tree->p->right = r;
        }
    }
    tree->p = r;



    //there must be smarter ways
    if(tree->max > r->max){
        r->max = tree->max;
        return;
    }

    if(tree->max == r->max){
        int m = max(tree->left,tree->right);
        if(m > tree->high){
            tree->max = m;
        }
        else{
            tree->max = tree->high;
        }

        int m_r = max(tree,r->right);
        if(m_r > r->high){
            r->max = m_r;
        }
        else{
            r->max = r->high;
        }


    }

}


interval* minimum_search(interval* i, int t1, int t2){
    interval* min = nullptr;
    while(i != nullptr){
        if(t1 <= i->high && i->low <= t2){
            if(i->low < min->low) min = i;
        }

        if(i->left != nullptr && i->left->max >= t1){
            i = i->left;
        }

        else{
            i = i->right;
        }
    }
    return min;
}

//14.3-4 find and remove it from the tree (simple) takes O(logN) for each removal, 
//solucao boa

interval* interval_search_exactly(interval* root, int t1, int t2){
    if(root == nullptr){
        return nullptr;
    }

    if(root->max < t2){
        return nullptr;
    }


    if(root->low == t1 && root->high == t2){
        return root;
    }
    
    if(t1 <= root->low){
        return interval_search_exactly(root->left,t1,t2);
    }
    else return interval_search_exactly(root->right,t1,t2);
}

//14.3-6
/*
as you insert, the closest to you are your ancestors, because between every brother/cousin there are people in between*/

// or let min gap be the minimum in the tree ??? actually i think this is wrong, as rotations might fuck up stuff

