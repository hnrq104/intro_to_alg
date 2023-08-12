#include <bits/stdc++.h>
using namespace std;

struct node{
    
    enum color{
        BLACK,
        GRAY,
        WHITE
    };

    uint vertex;
    uint d;
    uint f;
    node* next;
    color c;
    uint weight;

    node(){
        c = WHITE;
        next = nullptr;
    }
};

struct edge{
    int weight;
    uint a;
    uint b;
    edge* next;
};

/*
GENERIC-MST(G,w)
    A = nullset
    while A does not form a spanning tree
        find an edge(u,v) that is safe for A
        A = AU(u,v)
    
    return A
*/

/*find cycle with dfs*/
bool find_cycle_aux(vector<node> &adj_list, uint vertex, node* &list_ptr, node* &last_ptr,uint previous){
    adj_list.at(vertex).c = node::GRAY;

    node* ptr = adj_list.at(vertex).next;
    while(ptr!=nullptr){
        if(ptr->vertex!=previous){
            if(adj_list.at(ptr->vertex).c == node::GRAY){
                node *edge = new node;
                edge->vertex = ptr->vertex;
                edge->weight = ptr->weight;
                list_ptr = edge;
                last_ptr = edge;
                return true;
            }

            /*if theres a black node, it means we are not in a undirected graph*/

            if(adj_list.at(ptr->vertex).c == node::WHITE){
                bool answer = find_cycle_aux(adj_list,ptr->vertex,list_ptr,last_ptr,vertex);
                if(answer){
                    node* edge = new node;
                    edge->vertex = vertex;
                    edge->weight = ptr->weight;
                    edge->next = list_ptr->next;
                    list_ptr = edge;

                    if(last_ptr->vertex != ptr->vertex) return true;
                    else return false;

                }
            }
        }

        ptr = ptr->next;
    }

    return false;
}

node* find_cycle(vector<node> adj_list){
    for(uint i = 0; i < adj_list.size(); i++){
        adj_list.at(i).c = node::WHITE;
    }
    node* list;
    node* last;
    for(uint i = 0; i < adj_list.size(); i++){ //just to make forest viable
        if(adj_list.at(i).c == node::WHITE){
            list = nullptr;
            last = nullptr;
            find_cycle_aux(adj_list, i,list,last,-1);
            if(list!=nullptr){
                return list;
            }
        }
    }
    return nullptr;
}


/*23.1-11
add edge to tree T, it would create a cycle, find such cycle simply by using dfs,
run thru the cycle, remove the edge of biggest weight*/

vector<node> change_edge(vector<node> &tree_graph, uint a, uint b, int weight){
    /*copy graph*/
    vector<node> tree = tree_graph;
    for(uint i = 0; i < tree.size(); i++){
        node* ptr_graph = tree_graph.at(i).next;
        while(ptr_graph!= nullptr){
            node* tree_ptr = new node(*ptr_graph);
            tree_ptr->next = tree.at(i).next;
            tree.at(i).next = tree_ptr;

            ptr_graph = ptr_graph->next;
        }
    }
    
    /*add new edge to tree on both sides*/
    node* edge = new node;
    edge->vertex = b;
    edge->next = tree.at(a).next;
    edge->weight = weight;
    tree.at(a).next = edge;


    edge->vertex = a;
    edge->next = tree.at(b).next;
    edge->weight = weight;
    tree.at(b).next = edge;


    /*find cycle*/
    node* list = find_cycle(tree);
    /*find max node to be removed*/
    node* ptr = list;
    uint start;
    uint end;
    int max = INT_MIN;
    while(ptr->next != nullptr){
        if(ptr->next->weight > max){
            start = ptr->vertex;
            end = ptr->next->vertex;
            max = ptr->next->weight;
        }
        ptr = ptr->next;
    }

    /*remove this edge*/
    ptr = &tree.at(start);
    while (ptr->next!=nullptr) {
        if(ptr->next->vertex == end){
            node* destroy = ptr->next;
            ptr->next = destroy->next;
            delete destroy;
        }
        ptr = ptr->next;
    }
    

    ptr = &tree.at(end);
    while (ptr->next!=nullptr) {
        if(ptr->next->vertex == start){
            node* destroy = ptr->next;
            ptr->next = destroy->next;
            delete destroy;
        }
        ptr = ptr->next;
    }

    return tree;

}


