#include <bits/stdc++.h>


template<typename T>
class set{
    public:

    T element;
    set* parent;
    int rank;

    /*i will add id for exercise 21.1 and 21.3*/
    int id;

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

/*keeps id of rhs*/
template<typename T>
void link(set<T>* a, set<T>* b){
    if(a->rank > b->rank){
        b->parent = a;
        // a->id = b->id;
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
set<T>* find_set_iteractive(set<T>* a){
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


/*i need to identify which k each set belongs to,
this involves creating an id for each set struct
that tells each root what set it belongs to
overall this problem can be done in O(n*alfa(n)) */

/*or better as in the solution, create a linked list of sets each with its number*/

template <typename T>
struct node{
    T t;
    node* next;
    node* previous;

    node(){}

    node(T obj){
        t = obj;
    }

};

/*b is the node inserted of node a*/
template <typename T>
void insert_node_front(node<T>* a, node<T>* b){
    b->next = a->next;
    b->previous = a;
    a->next = b;
    b->next->previous = b;
}

template<typename T>
void remove_node(node<T> *a){
    a->previous->next = a->next;
    a->next->previous = a->previous;
}

template <typename T>
struct double_linked_list{
    node<T>* head;
    node<T>* tail;
    // int size;

    double_linked_list(){
        head = new node<T>;
        tail = new node<T>;
        // size = 0;
        head->previous = nullptr;
        head->next = tail;
        tail->previous = head;
        tail->next = nullptr;
    }

    void insert_back(node<T>* b){
        insert_node_front(tail->previous,b);
    }
};

/*i will suppose -1 = E, doesnt really matter*/
/*my sequence starts at 0*/



/*21.1*/
/*this is terrible, terrible code*/
std::vector<int> off_line_min(std::vector<int> sequence,int n, int m){
    std::vector<set<int>*> numbers(n); 
    //initialize numbers
    for(int i = 0; i < n; i++){
        numbers.at(i) = new set<int>(i);
    }


    //a set with -1 in it, means it's empty, as we will never query -1
    std::vector<set<int>*> sets(m+1);
    std::vector<node<int>*> nodes(m+1);
    double_linked_list<int> list;
    for(int i = 0; i <= m; i++){
        sets.at(i) = new set<int>(-1);
        sets.at(i)->id = i;

        node<int>* ptr = new node<int>(i);
        list.insert_back(ptr);
        nodes.push_back(ptr);
    
    }
    
    //insert into kj
    int j = 0;
    for(uint i = 0; i < sequence.size(); i++){
        int num = sequence.at(i);
        if(num == -1) j++;
        else{
            union_set(numbers.at(num), sets.at(j));
            numbers.at(num)->id = j;
        }
    }    

    std::vector<int> extracted(m);
    for(int i = 0; i < n; i++){
        int j = numbers.at(i)->find_set()->id;
        
        if(j==m) continue;

        extracted.at(j) = i;
        int l = nodes.at(j)->next->t;

        union_set(numbers.at(i), sets.at(l));
        numbers.at(i)->find_set()->id = l;
        remove_node(nodes.at(j));
    }

    return extracted;
}



/*21.3

LCA(U)
    make-set(u)
    find-set(u).ancestor = u
    for each child v of u in T
        LCA(v)
        UNION(u,v)
        find-set(u).ancestor = u

    u.color = black
    for each node v such that (u,v) in P
        if v.color == black
            print the least common ancestor of u and v is (find-set(v).ancestor)



honestly, i might do these later, not sure when*/

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