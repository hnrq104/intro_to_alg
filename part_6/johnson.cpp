#include <bits/stdc++.h>
#include "fib.hpp"

using namespace std;

struct node{
    uint vertex;
    node* next;
    uint parent;
    double d;
    double f; /*if an edge, will be weight*/
    bool color;

    node(){
        next = nullptr;
        color = false;
    }

};


void initialize_single_source(std::vector<node> &g, uint s){
    for(uint i = 0; i < g.size(); i++){
        g.at(i).d = DBL_MAX;
        g.at(i).parent = -1;
    }

    g.at(s).d = 0;
}

bool relax(std::vector<node> &g, uint u, uint v, double w){
    if(g.at(v).d > g.at(u).d + w){
        g.at(v).d = g.at(u).d + w;
        g.at(v).parent = u;
        return true;
    }

    return false;
}

/*dijkstra*/
void dijkstra(std::vector<node> &g, uint source){
    /*i need to associate fibnodes in the heap to intengers*/
    std::map<FibNode<double>*,uint> hashmap;
    std::vector<FibNode<double>*> track_of_nodes(g.size());
    FibonacciHeap<double> Q;

    initialize_single_source(g,source);
    for(uint i = 0; i < g.size(); i++){
        FibNode<double>* ptr = new FibNode(g.at(i).d);
        track_of_nodes.at(i) = ptr;
        hashmap.emplace(std::make_pair(ptr,i));
        Q.insert(track_of_nodes.at(i));
    }

    while(!Q.empty()){
        FibNode<double>* u_fib = Q.extract_min();
        uint u = hashmap.find(u_fib)->second;

        node* ptr = g.at(u).next;
        
        while(ptr!=nullptr){
            if(relax(g,u,ptr->vertex,ptr->f)){
                Q.decrease_key(track_of_nodes.at(ptr->vertex),g.at(ptr->vertex).d);
            }
            ptr = ptr->next;
        }
    }
}

/*bellman ford*/
bool bellman_ford(std::vector<node> &g, uint source){
    initialize_single_source(g,source);
    for(uint j = 0; j < g.size()-1; j++){ // i from 1 to |G.V| - 1
        bool change = false;
        for(uint i = 0; i < g.size(); i++){
            /*get all edges*/
            node* ptr = g.at(i).next;
            while(ptr!=nullptr){
                change = change || relax(g,i,ptr->vertex,ptr->f);
                ptr = ptr->next;
            }
        }

        if(!change) break; // nothing was changed in this iteration
    }

    /*now check for each edge*/

    for(uint i = 0; i < g.size()-1; i++){
        /*get all edges*/
        node* ptr = g.at(i).next;
        while(ptr!=nullptr){
            if(g.at(ptr->vertex).d > g.at(i).d + ptr->f){
                return false;
            }
            ptr = ptr->next;
        }
    }

    return true;
}


/*johnson */
vector<vector<double>> johnson(vector<node> &G){
    /*we will add a new vertex, at the end and connect it to everyone*/
    int n = G.size();
    G.push_back(node());
    for(int i = 0; i < n; i++){
        node* ptr = new node;
        ptr->vertex = i;
        ptr->f = 0;
        ptr->next = G.back().next;
        G.back().next = ptr;
    }

    if(!bellman_ford(G,G.size() - 1)){
        cout << "the graph contains a negative cycle" << endl;
        return vector<vector<double>>();
    }

    for(int i = 0; i < n; i++){
        node* ptr = G.at(i).next;
        while(ptr!=nullptr){
            ptr->f = ptr->f + G.at(i).d - G.at(ptr->vertex).d;
            ptr = ptr->next;
        }
    }

    vector<vector<double>> D(n,vector<double>(n));
    for(int i = 0; i < n; i++){
        dijkstra(G,i);
        for(int j = 0; j < n; j++){
            D.at(i).at(j) = G.at(j).d;
        }
    }

    return D;
}
