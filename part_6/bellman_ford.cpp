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

/*since chapter 24.2 is really small, i will write it here
single shortest path in dags*/

/*rewrite top sort here*/
void topological_recursion(uint i,std::vector<node> &adj, node* &list_head){
    adj.at(i).color = true;
    
    node* ptr = adj.at(i).next;
    while(ptr!=nullptr){
        if(!adj.at(ptr->vertex).color){
            topological_recursion(ptr->vertex,adj,list_head);
        }
        ptr = ptr->next;
    }

    node* number = new node;
    number->vertex = i;
    number->next = list_head->next;
    list_head->next = number;
}


/*this returns a linked list which only numbers matter, i'm using the node structure here
but i shouldn't really. As it's not really important right now, i could revisit it in the future*/
node* topological_sort(std::vector<node> adj){
    node* list_head  = new node;
    for(uint i = 0; i < adj.size(); i++){
        adj.at(i).color = false;
    }
    for(uint i = 0; i < adj.size(); i++){
        if(!adj.at(i).color){
            topological_recursion(i,adj,list_head);
        }
    }
    return list_head->next;
}

void dag_shortest_path(std::vector<node> &g, uint source){
    node* top_sort = topological_sort(g);
    initialize_single_source(g,source);
    while(top_sort != nullptr){
        /*relax for each vertex in topsort list*/
        node* ptr = g.at(top_sort->vertex).next;
        while(ptr!=nullptr){
            relax(g,top_sort->vertex,ptr->vertex,ptr->f);
            ptr = ptr->next;
        }
        top_sort=top_sort->next;        
    }

}



/*24.2-4 count all paths in a dag*/

int paths_dag_iterative(std::vector<node> &g){
    node* list = topological_sort(g);
    std::vector<int> paths(g.size(),0);
    /*i have to travel the list in reverse*/
    std::stack<int> stack;
    while(list!=nullptr){
        node* ptr = list->next;
        stack.emplace(list->vertex);
        delete list;
        list = ptr; /*i am deleting the list to save up memory, will be useful in the future*/
    }

    while(!stack.empty()){
        node* ptr = g.at(stack.top()).next;
        while(ptr!=nullptr){
            paths.at(stack.top()) += 1 + paths.at(ptr->vertex);
            ptr = ptr->next;
        }
        stack.pop();
    }

    int sum = 0;
    for(auto i : paths){
        sum += i;
    }
    return sum;
}

int main(void){
    std::cout << (DBL_MAX + 1.0 < DBL_MAX) << std::endl;
}