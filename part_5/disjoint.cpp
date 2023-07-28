#include <bits/stdc++.h>


template<typename T>
struct set{
    T element;
    set* parent;
    int rank;

    set(T t){
        element = t;
        parent = this;
        rank = 0;
    }

    set* find_set(void){
        if(parent == this){
            return this;
        }
        parent = parent->find_set();
        return parent;
    }
};

template<typename T>
void link(set<T>* a, set<T>* b){
    if(a->rank > b->rank){
        b->parent = a;
    }
    else{
        a->parent = b;
        if(a->rank == b->rank){
            b->rank++;
        }
    }
}

template <typename T>
void union_set(set<T>* a, set<T>* b){
    link(a->find_set(),b->find_set());
}

/*21.1 and 21.2 are in my notebook*/
/*exercise 21.3-2*/

template<typename T>
set<T>* find_set_interactive(set<T>* a){
    std::stack<set<T>*> path;
    set<T>* ptr = a;
    while(ptr->parent != ptr){
        path.push(ptr);
        ptr = ptr->parent;
    }

    while(!path.empty()){
        path.top()->parent = ptr;
        path.pop();
    }

    return ptr;
}



int main(void){
/*
    set<int> a;
    a.element = 3;

    set<double> b;
    b.element = 3.14;

    a.parent = b;
    b.parent = a;
*/

}