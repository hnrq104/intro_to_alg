#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct vertex{
    
    enum color{
        BLACK,
        GRAY,
        WHITE
    };

    T key;
    uint d;
    uint f;
    vertex* next;
    color c;
};

/*
GENERIC-MST(G,w)
    A = nullset
    while A does not form a spanning tree
        find an edge(u,v) that is safe for A
        A = AU(u,v)
    
    return A
*/

/*23.1-11
add edge to tree T, it would create a cycle, find such cycle simply by using dfs,
run thru the cycle, remove the edge of biggest weight*/

vector<vertex<uint>> new_mst(vector<vertex<uint>> adj_list,vector<vertex<uint>> tree,uint a, uint b, uint weight){
    
}
