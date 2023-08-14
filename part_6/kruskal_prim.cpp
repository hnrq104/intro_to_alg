#include <bits/stdc++.h>

template<typename T>
class set{
    public:

    T element;
    set* parent;
    int rank;

    /*i will add id for exercise 21.1 and 21.3*/
    // int id;

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

/*will use list*/

int main(void){
    std::vector<edge> minheap;
    minheap.push_back(edge(0,0,5));
    minheap.push_back(edge(0,0,10));
    minheap.push_back(edge(0,0,2));
    minheap.push_back(edge(0,0,20));
    minheap.push_back(edge(0,0,-5));

    std::sort(minheap.begin(),minheap.end());
    
    for(auto e : minheap){
        std::cout << e.weight << " ";
    }
    std::cout << std::endl;

    return 0;
}

