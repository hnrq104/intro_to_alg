#include <bits/stdc++.h>
#include <cstddef>

//lazy evaluation it seems

struct node{
    int key; //key in node
    int deegre; // number of childre
    node* p; // parent node
    node* l; //left in double linked list
    node* r; //right in double linked list
    node* child;
    bool mark; // if it has lost a child since subjugation

    node(int k){
        key = k;
    }
};

struct heap{
    node* min; //tree containing min key
    int n; // number of elements

    heap(){
        n = 0;
        min = nullptr;
    }

    void insert(node* x){
        x->deegre = 0;
        x->p = nullptr;
        x->mark = false;
        x->child = nullptr;  
        if(min == nullptr){
            min = x;
            /*if heap is empty, x is the first tree*/
            x->l=x;
            x->r=x;
        }

        else{
            /*add x to double linked list
            i will add to right of min
            */
            x->l = min->l;
            min->l = x;
            x->r = min;
            x->l->r = x;

            if(x->key < min->key){
                min = x;
            }
        }

        n++;
    }

    node* fib_heap_link(node* x, node* y){
        node* smaller;
        node* bigger;

        if(x->key < y->key){
            smaller = x;
            bigger = y;
        }
        else{
            smaller = y;
            bigger = x;
        }

        //add bigger to smallers child list
        if(smaller->child == nullptr){
            smaller->child = bigger;
        }
        else{
            bigger->l = smaller->child->l;
            bigger->r = smaller->child;
            smaller->child->l = bigger;
            bigger->l->r = bigger;
        }

        bigger->p = smaller;
        bigger->mark = false;
        smaller->deegre++;
        return smaller;
    }

    void consolidate(){
        /*while i cant calculate dn we will take d(n) to discover how many there are*/
        int size = 1;
        node* ptr = min->r;
        while(ptr != min){ //full circle
            size++;
            ptr = ptr->r;
        }

        std::vector<node*> a(size,nullptr);
        for(int i = 0; i < size; i++){
            node* next = ptr->r;
            node* x = ptr;

            x->r->l = x->l;
            x->l->r = x->r;
            x->l = x;
            x->r = x;
            int d = x->deegre;
            while(a.at(d) != nullptr){
                x = fib_heap_link(x,a.at(d));
                a.at(d) = nullptr;
                d++;
            }
            a.at(d) = x;

            if(ptr == next) break;
            ptr = next;
        }

        min = nullptr;
        for(int i = 0; i < size; i++){
            if(a.at(i) != nullptr){
                if(min == nullptr){
                    min = a.at(i);
                    min->r = min;
                    min->l = min;
                }

                else{
                    a.at(i)->l = min->l;
                    a.at(i)->r = min;
                    min->l = a.at(i);
                    min->l->r = a.at(i);

                    if(a.at(i)->key < min->key){
                        min = a.at(i);
                    }
                    
                }
            }
        }
        /*this is terrible code, wtf, using circular lists is so stupid
        if i apply lazy evaluation to mine is way better(may do later, improbable)*/
    }


    node* extract_min(){
        if(min == nullptr) return nullptr;
        
        node* z = min;
        node* ptr = z->child;
        if(ptr != nullptr){    
            do{ /*using do while is absolutely agains all my wishes*/
                node* next = ptr->r;
                ptr->l = min->l;
                ptr->r = min;
                min->l = ptr;
                ptr->l->r = ptr;
                ptr->p = nullptr;
                ptr = next;
            } while (ptr!=z->child);
            
        }

        z->l->r = z->r;
        z->r->l = z->l;

        if(z == z->r){
            min = nullptr;
        }
        else{
            min = z->r;
            consolidate();
        }
        n--;

        return z;

    }

};

heap fib_heap_union(heap h1, heap h2){
    if(h1.min == nullptr){
        return h2;
    }

    if(h2.min == nullptr){
        return h1;
    }

    node* b1 = h1.min->r; 
    node* b2 = h2.min->l;
    h1.min->r= h2.min;
    h2.min->l = h1.min;
    b1->l = b2;
    b2->r = b1;

    heap h;
    h.min = h1.min;

    if(h2.min->key < h1.min->key){
        h.min = h2.min;
    }
    
    h.n = h1.n + h2.n;
    
    return h;
    /*not using pointers, don't know if its best*/

}

int main(void){
    heap h;
    
    std::vector<int> keys = {10,20,15,12,17,9};
    std::cout << "starting insertion:" << std::endl;
    for(uint i = 0; i < keys.size(); i++){
        h.insert(new node(keys.at(i)));
    }
    std::cout << "inserted key items:" << std::endl;

    std::cout << "extracting min" << std::endl;
    node* ptr = h.extract_min();
    std::cout << ptr->key << std::endl;
    
    std::cout << "extracting min second time" << std::endl;
    ptr = h.extract_min();
    std::cout << ptr->key << std::endl;
    
    return 0;
}
