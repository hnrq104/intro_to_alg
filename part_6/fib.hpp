#include <bits/stdc++.h>

template<typename T>
struct FibNode{
    T key; //key in FibNode<T>
    int deegre; // number of childre
    FibNode<T>* p; // parent FibNode<T>
    FibNode<T>* l; //left in double linked list
    FibNode<T>* r; //right in double linked list
    FibNode<T>* child;
    bool mark; // if it has lost a child since subjugation

    FibNode(){}

    FibNode(T k){
        key = k;
    }
};

template<typename T>
class FibonacciHeap{
    public:
    FibNode<T>* min; //tree containing min key
    int n; // number of elements

    FibonacciHeap(){
        n = 0;
        min = nullptr;
    }

    void print_root_list(void){
        if(min == nullptr) return;
        
        FibNode<T>* ptr = min;
        do{
            std::cout << ptr->key << std::endl;
            ptr = ptr->l;
        }while(ptr != min);
        
    }

    void insert(FibNode<T>* x){
        x->deegre = 0;
        x->p = nullptr;
        x->mark = false;
        x->child = nullptr;  
        if(min == nullptr){
            min = x;
            /*if FibonacciHeap<T> is empty, x is the first tree*/
            x->l=x;
            x->r=x;
        }

        else{
            /*add x to double linked list
            i will add to the left of min
            */
            x->r = min;
            x->l = min->l;
            min->l = x;
            x->l->r = x;

            if(x->key < min->key){
                min = x;
            }
        }

        n++;
    }

    FibNode<T>* heap_link(FibNode<T>* x, FibNode<T>* y){
        FibNode<T>* smaller;
        FibNode<T>* bigger;

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
        int max_deegre = min->deegre;
        FibNode<T>* ptr = min->r;
        while(ptr != min){ //full circle
            if(ptr->deegre > max_deegre) max_deegre = ptr->deegre;
            size++;
            ptr = ptr->r;
        }

        std::vector<FibNode<T>*> a(max_deegre+3,nullptr);
        for(uint i = 0; i < size; i++){
            FibNode<T>* next = ptr->r;
            FibNode<T>* x = ptr;

            x->r->l = x->l;
            x->l->r = x->r;
            x->l = x;
            x->r = x;
            int d = x->deegre;
            while(a.at(d) != nullptr){
                x = heap_link(x,a.at(d));
                a.at(d) = nullptr;
                d++;
                if(d == a.size()) a.push_back(nullptr);
            }
            
            a.at(d) = x;

            if(ptr == next) break;
            ptr = next;
        }

        min = nullptr;
        for(uint i = 0; i < a.size(); i++){
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
                    a.at(i)->l->r = a.at(i);

                    if(a.at(i)->key < min->key){
                        min = a.at(i);
                    }
                    
                }
            }
        }
        /*this is terrible code, wtf, using circular lists is so stupid
        if i apply lazy evaluation to mine is way better(may do later, improbable)*/
    }

    FibNode<T>* extract_min(){
        if(min == nullptr) return nullptr;
        
        FibNode<T>* z = min;
        FibNode<T>* ptr = z->child;
        if(ptr != nullptr){    
            do{ /*using do while is absolutely agains all my wishes*/
                FibNode<T>* next = ptr->r;
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
    
    /*y has to be x parent*/
    void cut(FibNode<T>* x, FibNode<T>* y){
        /*remove x from y list*/
        if(y->deegre == 1){ //x is y's only child
            y->child = nullptr;
        }
        else{
            y->child = x->r;
            x->l->r = x->r;
            x->r->l = x->l;
        }
        y->deegre--;

        /*add x to root list*/
        x->p = nullptr;
        x->l = min->l;
        x->r = min;
        min->l = x;
        x->l->r = x;

        x->mark = false;
    }

    void cascading_cut(FibNode<T>* y){
        // FibNode<T>* z = y->p;
        if(y->p != nullptr){
            if(y->mark == false){
                y->mark = true;
            }
            else{
                cut(y,y->p); //i particularly dont like calling it z
                cascading_cut(y->p);
            }
        }
    }

    void decrease_key(FibNode<T>* x, T k){
        if(k>x->key) throw std::invalid_argument("new key is greater than current");
        x->key = k;
        FibNode<T>* y = x->p;
        if(y!= nullptr && x->key < y->key){
            cut(x,y);
            cascading_cut(y);
        }
        if(x->key < min->key){
            min = x;
        }
    }

    void delete_node(FibNode<T>*x){
        decrease_key(x, INT32_MIN);
        extract_min();
    }

};

template<typename T>
FibonacciHeap<T> heap_union(FibonacciHeap<T> h1, FibonacciHeap<T> h2){
    if(h1.min == nullptr){
        return h2;
    }

    if(h2.min == nullptr){
        return h1;
    }

    FibNode<T>* b1 = h1.min->r; 
    FibNode<T>* b2 = h2.min->l;
    h1.min->r= h2.min;
    h2.min->l = h1.min;
    b1->l = b2;
    b2->r = b1;

    FibonacciHeap<T> h;
    h.min = h1.min;

    if(h2.min->key < h1.min->key){
        h.min = h2.min;
    }
    
    h.n = h1.n + h2.n;
    
    return h;
    /*not using pointers, don't know if its best*/

}