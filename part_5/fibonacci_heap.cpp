#include <bits/stdc++.h>
#include <cstddef>
#include <cstdint>
#include <stdexcept>

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

    void print_root_list(void){
        if(min == nullptr) return;
        
        node* ptr = min;
        do{
            std::cout << ptr->key << std::endl;
            ptr = ptr->l;
        }while(ptr != min);
        
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
            std::cout<< "opa" << std::endl;
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
    void cut(node* x, node* y){
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

    void cascading_cut(node* y){
        // node* z = y->p;
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

    void decrease_key(node* x, int k){
        if(k>x->key) throw std::invalid_argument("new key is greater than current");
        x->key = k;
        node* y = x->p;
        if(y!= nullptr && x->key < y->key){
            cut(x,y);
            cascading_cut(y);
        }
        if(x->key < min->key){
            min = x;
        }
    }

    void delete_node(node*x){
        decrease_key(x, INT32_MIN);
        extract_min();
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

void print_tree(node* pt){
    std::cout << pt->key;

    if(pt->child != nullptr){
        node* aux = pt->child;
        do{
            std::cout << "(";
            print_tree(aux);
            std::cout << ")";
            aux = aux->r;
        }while (aux!=pt->child);
    }
}

int main(void){
    heap h;
    

    node* ptr = new node(7);
    node* ptr1 = new node(27);

    h.insert(new node(10));
    h.insert(new node(29));
    h.insert(new node(5));
    h.insert(ptr);

    h.insert(new node(0));
    h.insert(new node(3));
    h.insert(new node(2));
    h.insert(ptr1);

    h.extract_min();

    std::cout << "PRINTING" <<std::endl;
    h.print_root_list();

    h.decrease_key(ptr1, 1);
    h.decrease_key(ptr, -5);

    std::cout << "PRINTING" <<std::endl;
    h.print_root_list();
    
    std::cout << "EXTRACTING : " << h.extract_min()->key << std::endl;

    std::cout << "SIZE : " << h.n << std::endl;
    // std::cout << h.extract_min()->key << std::endl;
    // std::cout << "PRINTING" <<std::endl;
    // h.print_root_list();
    // std::cout << "min deegre :: " <<  h.min->deegre << std::endl;
    // std::cout << "min-l deegre :: " <<  h.min->l->deegre << std::endl;
    // std::cout<< "min l = " << h.min->l << " min r = " << h.min->r << std::endl;
    // std::cout<< "min l key = " << h.min->l->key << " min r key= " << h.min->r->key << std::endl;
    // std::cout << "MIN TREE : ";
    // print_tree(h.min);
    // std::cout << std::endl;

    // h.extract_min();
    // std::cout << "PRINTING" <<std::endl;
    // h.print_root_list();

    

    return 0;
}

/*
19.3

19.3-1 you might extract a node, making an already marked node into a new root
because it might never me linked below another, it would still be marked

*/