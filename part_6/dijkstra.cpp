#include<bits/stdc++.h>
#include "fib.hpp"

/*I repeat these for these are only for example, if one day i need to implement them, 
i will remember what i had found*/
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