#include <bits/stdc++.h>

struct fruta{
    int data;
    fruta *ant;
    fruta *esq;
    fruta *dir;
};


void inserir(fruta* &ptr, int d){
    if(ptr == nullptr){
        ptr = new fruta;
        ptr->data = d;
        ptr->esq = nullptr;
        ptr->dir = nullptr;
        return;
    }

    if(d < ptr->data){
        inserir(ptr->esq,d);
        ptr->esq->ant = ptr;
    }
    else{
        inserir(ptr->dir,d);
        ptr->dir->ant = ptr;

    }
}

fruta* &min(fruta* &ptr){
    while (ptr->esq != nullptr){
        ptr = ptr->esq;
    }
    return ptr;
}

fruta* &max(fruta* &ptr){
    while(ptr->dir != nullptr){
        ptr = ptr->dir;
    }
    return ptr;
}

void print(fruta* ptr){
    if(ptr == nullptr) return;

    print(ptr->esq);
    std::cout << ptr->data << std::endl;
    print(ptr->dir);
}

void post_print(fruta* salada){
    if(salada == nullptr) return;
    
    post_print(salada->dir);
    std::cout << salada->data << std::endl;
    post_print(salada->esq);
}


void inorder_walk(fruta* salada){
    std::vector<fruta*> stack;

    // stack.push_back(salada);
    fruta *ptr = salada;
    while(true){
        while(ptr!= nullptr){
            stack.push_back(ptr);
            ptr = ptr->esq;
        }

        if(stack.size() == 0) break;

        ptr = stack.back();
        stack.pop_back();
        std::cout << ptr->data << std::endl;
        
        ptr = ptr->dir;
    }
}

fruta* tree_successor(fruta* ptr){
    if(ptr->dir != nullptr){
        return min(ptr->dir);
    }

    //else
    fruta* prev = ptr->ant;
    fruta* pt = ptr;   
    while(prev != nullptr && pt != prev->dir){
        pt = prev;
        prev = prev->ant;
    }

    return prev;
}

fruta* &min_rec(fruta* &ptr){
    if(ptr->esq == nullptr){
        return ptr;
    }
    return min_rec(ptr->esq);
}


fruta* &max_rec(fruta* &ptr){
    if(ptr->dir == nullptr){
        return ptr;
    }
    return min_rec(ptr->dir);
}

fruta* tree_predecessor(fruta* ptr){
    if(ptr->esq != nullptr){
        return max(ptr->esq);
    }

    //else
    fruta* prev = ptr->ant;
    while(prev != nullptr && ptr != prev->esq){
        ptr = prev;
        prev = prev->ant;
    }
    return prev;
}

void transplant(fruta* antigo, fruta* trocado){
    if(antigo->ant == nullptr){
        antigo = trocado;
    }
    else if (antigo == antigo->ant->esq){
        antigo->ant->esq = trocado;
    }
    else{
        antigo->ant->dir = trocado;
    }

    if(trocado != nullptr){
        trocado->ant = antigo->ant;
    }
}

void deletar(fruta* &del){
    if(del->esq == nullptr){
        transplant(del,del->dir);
    }

    else if(del->dir == nullptr){
        transplant(del,del->esq);
    }

    else{
        fruta* ptr = min(del->dir);
        if(ptr->ant == del){
            transplant(ptr,ptr->dir);
            ptr->dir = del->dir;
            ptr->dir->ant = del;
        }

        transplant(del,ptr);
        ptr->esq = ptr->esq;
        ptr->esq->ant = ptr; 
    }
}



/*
void elegant_walk(fruta *salada){
}
*/


struct verdura{
    int dado;
    verdura *left;
    verdura *right;
    verdura *succ;

    verdura(int n){
        dado = n;
        left = nullptr;
        right = nullptr;
        succ = nullptr;
    }
};


void ver_inser(verdura* &root, int n){
    if(root == nullptr){
        root = new verdura(n);
        return;
    }

    verdura *antecessor = nullptr;
    verdura *sucessor = nullptr;

    verdura *ant_ptr = nullptr;
    verdura *ptr = root;
    while(ptr != nullptr){
        ant_ptr = ptr;

        if(n >= ptr->dado){
            antecessor = ptr;
            ptr = ptr->right;
        }

        else{ //n < ptr->dado
            sucessor = ptr;
            ptr = ptr->left;
        }
    }

    ptr = new verdura(n);

    if(n >= ant_ptr->dado){
        ant_ptr->right = ptr;
    }
    else{
        ant_ptr->left = ptr;
    }

    if(antecessor != nullptr){
        verdura* suc_ant = antecessor->succ;
        if(suc_ant == nullptr){
            antecessor->succ = ptr;
        }
        else if(suc_ant->dado > n){
            antecessor->succ = ptr;
        }

    }
    ptr->succ = sucessor;
}

void print_suc(verdura *ptr){
    if(ptr == nullptr) return;
    print_suc(ptr->left);
    std::cout << ptr->dado;
    if(ptr->succ != nullptr){
        std::cout << " - > "  << ptr->succ->dado;
    }
    std::cout << std::endl;
    print_suc(ptr->right);
}


int main(void){
    // fruta* root = nullptr;

    // inserir(root,10);
    // inserir(root,4);
    // inserir(root,5);
    // inserir(root,2);
    // inserir(root,3);

    // std::cout << "recursivo " << std::endl;
    // print(root);

    // std::cout << "usando stack " << std::endl;
    // inorder_walk(root);

    verdura* salad = nullptr;
    ver_inser(salad, 3);
    ver_inser(salad, 2);
    ver_inser(salad, 1);
    ver_inser(salad, 7);
    ver_inser(salad, 4);
    ver_inser(salad, 9);
    ver_inser(salad, 5);

    print_suc(salad);


    return 0;
}   