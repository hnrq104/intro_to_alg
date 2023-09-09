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

    void nova_aresta(int destino, double peso){
        node* ptr = new node;
        ptr->f = peso;
        ptr->vertex = destino;
        ptr->next = next;
        next = ptr;
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

bool bellman_ford(std::vector<node> &g, uint source){
    initialize_single_source(g,source);
    for(uint j = 0; j < g.size()-1; j++){ // i from 1 to |G.V| - 1
        bool change = false;
        for(uint i = 0; i < g.size(); i++){
            /*get all edges*/
            node* ptr = g.at(i).next;
            while(ptr!=nullptr){
                if(relax(g,i,ptr->vertex,ptr->f)) change = true; /*this was insane*/
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
