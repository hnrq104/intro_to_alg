#include <bits/stdc++.h>


template<typename T>
class set{
    public:

    T element;
    set* parent;
    int rank;

    /*i will add id for exercise 21.1 and 21.3*/
    int id;

    set(T t, int i){
        element = t;
        parent = this;
        rank = 0;
        id = i;
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
        a->id = b->id;
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

/*i will suppose -1 = E, doesnt really matter*/
/*my sequence starts at 0*/

/*i need to identify which k each set belongs to,
this involves creating an id for each set struct
that tells each root what set it belongs to
overall this problem can be done in O(n*alfa(n)) */

/*or better as in the solution, create a linked list of sets each with its number*/

/*
std::vector<int> off_line_min(std::vector<int> sequence,int n, int m){
    std::vector<set<int>*> numbers(n); 
    //initialize numbers
    for(int i = 0; i < n; i++){
        numbers.at(i) = new set<int>(i,0);
        //these sets id don't matter
    }

    //a set with -1 in it, means it's empty, as we will never query -1
    std::vector<set<int>*> sets(m+1);
    for(int i = 0; i <= m; i++){
        sets.at(i) = new set<int>(-1,i);
    }
    
    //insert into kj
    int j = 0;
    for(uint i = 0; i < sequence.size(); i++){
        int num = sequence.at(i);
        if(num == -1) j++;
        else union_set(numbers.at(num), sets.at(j)); //will keep sets.at(j) id
    }    
}
*/


/*problem 21.1 and 21.3*

/*honestly, i might do these later, not sure when*/

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