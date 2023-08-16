#include <bits/stdc++.h>
#include "fib.hpp"

template<typename T>
class set{
    public:

    T element;
    set* parent;
    int rank;

    /*i will add id for exercise 21.1 and 21.3*/
    // int id;
    set(){}

    set<T>(T &t){
        element = t;
        parent = this;
        rank = 0;
    }

    set<T>* find_set(void){
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



struct edge{
    uint a;
    uint b;
    int weight;

    edge(uint src, uint dest, int w){
        a = src;
        b = dest;
        weight = w;
    }

    bool operator<(edge &rhs){
        return weight < rhs.weight;
    }
};

// bool less_than(edge &a, edge)

std::vector<edge> kruskal(std::vector<edge> edges){
    std::sort(edges.begin(),edges.end());
    uint m = 0;
    for(auto e : edges){
        if(e.a > m) m = e.a;
        if(e.b > m) m = e.b;
    }
    std::vector<set<uint>> sets(m+1);

    std::vector<edge> a;
    for(auto e :edges){
        if(sets.at(e.a).find_set() != sets.at(e.b).find_set()){
            a.push_back(e);
            union_set(&sets.at(e.a), &sets.at(e.b));
        }
    }

    return a;
}


/*need fibonacci heap for prim should I rewrite it?*/

/*PRIM

MST_PRIM(G,w,r){ 
    for each u in G.V
        u.key = INFTY
        u.p = nullptr
    
    r.key = 0
    Q = G.V

    while(Q != empty set)
        u = ExtractMin(Q)
        for each v in G.adj[u]
            if v in Q and w(u,v) < v.key
                v.p = u
                v.key = w(u,v)
}
*/

/* i will make it without a fib heap, which is bad, because i will write
it with lazy evaluation*/

struct vertex{
    int v;
    int p;
    double key;
    
    bool operator<(vertex &rhs){
        return key < rhs.key;
    }

    bool operator>(vertex &rhs){
        return key > rhs.key;
    }

    bool operator<=(vertex &rhs){
        return key <= rhs.key;
    }

    bool operator>=(vertex &rhs){
        return key >= rhs.key;
    }
};

struct node{
    uint vertex;
    node* next;
    uint parent;
    uint d; /*i will suppose this is  weight*/
    uint f;
    bool color;

    node(){
        next = nullptr;
        color = false;
    }

};

/*this changes the p attribute in each node*/
void prim(std::vector<node> &G, int r){
    std::unordered_map<FibNode<double>*, uint> dict;
    std::vector<FibNode<double>*> list(G.size());
    for(uint i = 0; i < G.size(); i++){
        list.at(i) = new FibNode<double>(DBL_MAX);
        dict.insert(std::make_pair(list.at(i),i));
    }

    list.at(r)->key = 0;
    std::vector<bool> in_tree(G.size());
    /*i will set parents at G*/

    FibonacciHeap<double> Q;
    for(auto itr:list){
        Q.insert(itr);
    }

    while(Q.n>0){
        FibNode<double> *ptr = Q.extract_min();
        uint vertex = dict.find(ptr)->second;
        in_tree.at(vertex) = true;

        node* edges = G.at(vertex).next;
        while(edges != nullptr){
            if(!in_tree.at(edges->vertex)){
                if(edges->d < list.at(edges->vertex)->key){
                    Q.decrease_key(list.at(edges->vertex), edges->d);
                    G.at(edges->vertex).parent = vertex;
                }
            }
            edges = edges->next;
        }
    }
    
}

int main(void){
    FibonacciHeap<int> fib;
    for(int i = 0; i < 10; i++){
        fib.insert(new FibNode<int>(i));
    }

    while(fib.n > 0){
        std::cout << fib.extract_min()->key << std::endl; 
    }
    return 0;
}

