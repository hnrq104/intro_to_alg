#include <bits/stdc++.h>

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

std::vector<node> transpose_graph(std::vector<node> &g){
    std::vector<node> transposed(g.size());
    for(uint i = 0; i < g.size(); i++){
        node* ptr = g.at(i).next;
        while(ptr!=nullptr){
            node* edge = new node;
            edge->vertex = i;
            edge->next = transposed.at(ptr->vertex).next;
            transposed.at(ptr->vertex).next = edge;

            ptr = ptr->next;
        }
    }

    return transposed;
}

/*24.1-5*/
bool min_star(std::vector<node> &g, uint source){
    std::vector<node> t = transpose_graph(g);
    bool no_cycle = bellman_ford(t,source);
    for(uint i = 0; i < g.size(); i++){
        g.at(i).d = t.at(i).d;
    }
    return no_cycle;
}


int main(void){
    std::cout << (DBL_MAX + 1.0 < DBL_MAX) << std::endl;
}