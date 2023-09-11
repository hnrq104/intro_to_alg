#include <bits/stdc++.h>
using namespace std;
struct node{
    uint vertex;
    uint height;
    double e;
    list<node*> neighbors;
    list<node*>::iterator current;
};

struct graph{
    double flow;
    double capacity;
};


//the algorithm is already V^3, using matrices wont change it much
//we should update the value in Gf instantaneously aswell, which is why matrices seem better
void push(vector<node> &nodes,vector<vector<graph>> &flow,vector<vector<double>> &Gf, uint u, uint v){
    // applies when : u is overflowing (e(u) > 0), cf(u,v) > 0 and u.h = v.h + 1
    //action: pushes over min(e(u),cf(u,v)) from u to v
    double delta_f = min(nodes.at(u).e, Gf.at(u).at(v));
    
    if(flow.at(u).at(v).capacity != 0){
        flow.at(u).at(v).flow += delta_f;
        
        Gf.at(u).at(v) -= delta_f;
        Gf.at(v).at(u) += delta_f;
    }
    else{
        flow.at(v).at(u).flow -= delta_f;
        Gf.at(v).at(u) += delta_f;
        Gf.at(u).at(v) -= delta_f;
    }
    
    nodes.at(u).e -=  delta_f;
    nodes.at(v).e += delta_f;
}

void relable(vector<node> &nodes, uint u, vector<vector<double>> &Gf){
    /*will do dumb way no, i don't need to*/
    uint min_height = (*(nodes.at(u).current))->height;
    for(auto &n : nodes.at(u).neighbors){
        if(Gf.at(u).at(n->vertex) != 0){
            if(min_height < n->height) min_height = n->height;
        }
    }
    nodes.at(u).height = min_height + 1;
}

void initialize_pre_flow(vector<node> &nodes, uint s,vector<vector<graph>> &G , vector<vector<double>> &Gf){
    for(auto &v : nodes){
        v.e = 0;
        v.height = 0;
    }

    for(uint i = 0; i < G.size(); i++){
        for(uint j = 0; j < G.size(); j++){
            G.at(i).at(j).flow = 0;
            Gf.at(i).at(j) = G.at(i).at(j).capacity;
        }
    }

    nodes.at(s).height = G.size();
    
    for(uint i = 0; i < G.size(); i++){
        if(G.at(s).at(i).capacity){
            G.at(s).at(i).flow = G.at(s).at(i).capacity;
            nodes.at(i).e = G.at(s).at(i).capacity;
            nodes.at(s).e -= G.at(s).at(i).capacity;

            /*update Gf*/
            Gf.at(s).at(i) = 0;
            Gf.at(i).at(s) = G.at(s).at(i).capacity;

        }
    }
}


void discharge(vector<node> &nodes, uint u, vector<vector<double>> &Gf, vector<vector<graph>> &G){
    while(nodes.at(u).e > 0){
        auto v = nodes.at(u).current;
        if(v == nodes.at(u).neighbors.end()){
            relable(nodes,u,Gf);
            nodes.at(u).current = nodes.at(u).neighbors.begin();
        }
        else if(Gf.at(u).at((*v)->vertex)){
            push(nodes,G,Gf,u,(*v)->vertex);
        }
        else nodes.at(u).current = v++;
    }
}


void relable_to_front(vector<vector<graph>> &G, uint source, uint sink){
    vector<vector<double>> Gf(G.size(),vector<double>(0,G.size()));
    /*initialize node list*/
    vector<node> nodes(G.size());
    
    /*add edges to lists*/
    for(uint i = 0; i < G.size(); i++){
        for(uint j = 0; j < G.size(); j++){
            if(G.at(i).at(j).capacity != 0){
                nodes.at(i).neighbors.push_front(&nodes.at(j));
                nodes.at(j).neighbors.push_front(&nodes.at(i));

            }
        }
    }

    for(uint i = 0; i < nodes.size(); i++){
        nodes.at(i).vertex = i;
        nodes.at(i).current = nodes.at(i).neighbors.begin();
    }

    /*preflow*/
    initialize_pre_flow(nodes,source,G,Gf);

    /*INITIALZI LIST L TOPOLOGICALLY SORTED DAG*/
    list<node*> L;
    for(uint i = 0; i < nodes.size(); i++){
        if(i == source || i == sink) continue;
        L.push_front(&nodes.at(i));
    }

    auto u = L.begin();
    while(u != L.end()){
        uint old_h = (*u)->height;
        discharge(nodes,(*u)->vertex,Gf,G);

        if(old_h != (*u)->height){
            node* ptr = *u;
            L.erase(u);
            L.push_front(ptr);
            u = L.begin();
        }
        u++;

    }

}

/*
DISCHARGE(u)
    while(e(u) > 0)
        v = u.current
        if v == NIL
            RELABLE(u)
            u.current = u.N.Head
        elseif cf(u,v) > 0 and u.h == v.h + 1:
            push(u,v)
        else u.current = v.next_neighbor
*/

/*
RELABLE-TO-FRONT(G,s,t)
    Initialize preflow (G,s)
    L = G.V - {s,t}
    for each vertex u in G.V - {s,t}
        u.current = u.N.Head
    u = L.head

    while(u!=nil)
        old_h = u.h
        Discharge(U)
        
        if(old_h != u.h) //u was relabled
            move u to front of L
        
        u = u.next
*/