/*
14.1
*/

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
        if(y = y->p->right){
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

    if(x->key > a)
}
