#include <bits/stdc++.h>

struct node{
    uint vertex;
    node* next;
    uint parent;
    uint d;
    uint f;
    bool color;

    node(){
        next = nullptr;
        color = false;
    }

};
/*chapter 22.1*/

/*a simplified graph is one that contains no self loops or equal edges
this is exercise 22.1-4*/
std::vector<node> simplified_graph(std::vector<node> &multigraph){
    std::vector<uint> last(multigraph.size());
    std::vector<node> simplified(multigraph.size());

    for(uint i = 0; i < multigraph.size(); i++){
        node* ptr = multigraph.at(i).next;
        while(ptr!=nullptr){
            uint vertex = ptr->vertex;
            if(vertex != i && last.at(vertex) != i){
                last.at(vertex) = i;
                node* edge = new node;
                edge->vertex = vertex;
                edge->next = simplified.at(i).next;
                simplified.at(i).next = edge;
            }
            ptr = ptr->next;
        }
    }
    return simplified;
}

/*i will represent a adjacency-matrix by a matrix*/


/*similar to before, but we go into each edge looking for unconnected vertices*/
/*22.1-5*/
std::vector<node> square_graph(std::vector<node> &directedgraph){
    std::vector<uint> last(directedgraph.size());
    std::vector<node> square(directedgraph.size());

    for(uint i = 0; i < directedgraph.size(); i++){
        node* ptr = directedgraph.at(i).next;
        while(ptr!=nullptr){
            uint vertex = ptr->vertex;
            if(vertex != i && last.at(vertex) != i){
                last.at(vertex) = i;
                node* edge = new node;
                edge->vertex = vertex;
                edge->next = square.at(i).next;
                square.at(i).next = edge;
            }

            /*do the same inside vertex now*/
            node* vertex_ptr = directedgraph.at(vertex).next;
            while(vertex_ptr!= nullptr){
                uint num = vertex_ptr->vertex;
                if(num != i && last.at(num) != i){
                    last.at(num) = i;
                    node* edge = new node;
                    edge->vertex = num;
                    edge->next = square.at(i).next;
                    square.at(i).next = edge;
                }
                    
            }

            ptr = ptr->next;
        }
    }
    return square;
}

/*this runs in O(V + VE), for each edge we look into another edge set, consider a complete graph*/

/*to determine squareG we just have to square the matrix which is a bit crazy to think about*/
 

/*chapter 22.2*/


struct sol{
    std::vector<int> distances;
    std::vector<int> parent;
};

sol bfs(std::vector<node> adjacency, uint s){
    uint adj_size = adjacency.size();
    std::vector<int> distances(adj_size,INT32_MAX);
    std::vector<bool> visited(adj_size, false);
    std::vector<int> parent(adj_size,-1);
    
    std::queue<int> nodes;
    distances.at(s) = 0;
    visited.at(s) = true;
    nodes.push(s);
    // parent.at(s) = -1;

    while(!nodes.empty()){
        int n = nodes.front();
        nodes.pop();

        node* ptr = adjacency.at(n).next;
        while(ptr!=nullptr){
            if(visited.at(ptr->vertex) == false){
                visited.at(ptr->vertex) = true;
                distances.at(ptr->vertex) = distances.at(n) + 1;
                parent.at(ptr->vertex) = n;
                nodes.push(ptr->vertex);
            }
            ptr = ptr->next;
        }

    }
    sol answer;
    answer.distances = distances;
    answer.parent = parent;

    return answer;
}


/*baby-face and wheels 22.1-7*/

/*i could add that if it isn't possible, it would return a second value,
but the question only asks to bring corrected values if possible*/
std::vector<bool> baby_face(std::vector<node> adj){
    std::vector<bool> color(adj.size());
    std::vector<bool> visited(adj.size());
    int i = 0;
    while(true){
        while(i < visited.size() && visited.at(i)) i++;
        if(i>= visited.size()) break;
        
        std::queue<int> next;
        color.at(i) = true;
        visited.at(i) = true;
        /*i will always start connected components by a baby face*/
        next.push(i);

        while(!next.empty()){
            int num = next.front();
            next.pop();
            node* ptr = adj.at(num).next;

            while(ptr != nullptr){
                if(visited.at(ptr->vertex) == false){
                    visited.at(ptr->vertex) = true;
                    color.at(ptr->vertex) = !color.at(num);
                    next.push(ptr->vertex);
                }

                ptr = ptr->next;
            }
        }
    }

    return color;
}

/*22.2-8*/
int diamater_a_bit_slow(std::vector<node> adj){
    /*could do bfs twice and return farthest note, which is the easiest*/
    sol s = bfs(adj,0);
    int max = 0;
    for(int i = 0; i < s.distances.size(); i++){
        if(s.distances.at(max) < s.distances.at(i)) max = i;
    }
    s = bfs(adj,max);
    max = 0;
    for(int i = 0; i < adj.size(); i++){
        if(s.distances.at(max) < s.distances.at(i)) max = i;
    }
    return s.distances.at(max);

    /*this is not much productive and allocates a lot of unnecessary space*/
}

/*22.2-8*/
int diamater(std::vector<node> tree){
    std::vector<bool> visited(tree.size(), false);
    /*start at 0*/
    std::queue<int> q;
    q.push(0);

    int last;
    while(!q.empty()){
        last = q.front();
        q.pop();

        node* ptr = tree.at(last).next;
        while(ptr != nullptr){
            if(!visited.at(ptr->vertex)){
                q.push(ptr->vertex);
            }
            ptr = ptr->next;
        }
    }

    std::vector<int> distances;
    for(uint i = 0; i < visited.size(); i++){
        visited.at(i) = false;
    }

    visited.at(last) = true;
    distances.at(last) = 0;
    q.push(last);

    int num;
    while(!q.empty()){
        num = q.front();
        q.pop();

        node* ptr = tree.at(num).next;
        while(ptr!=nullptr){
            if(!visited.at(ptr->vertex)){
                distances.at(ptr->vertex) = distances.at(num) + 1;
                visited.at(ptr->vertex) = true;
                q.push(ptr->vertex);
            }
            ptr = ptr->next;
        }
    }

    return distances.at(num);
}

/*chapter 22.3*/


/*i could have made t a refernce value, which would be considerably easier, but this is just cooler*/
/*i will comment the changes anyway*/
int dfs_visit(uint source,std::vector<node> &tree,std::vector<node> adj, uint /*&*/t){
    tree.at(source).color = true;
    tree.at(source).d = t;

    node* ptr = adj.at(source).next;
    /*t++*/
    while(ptr!=nullptr){
        if(!tree.at(ptr->vertex).color){
            node* element = new node;
            element->vertex = ptr->vertex;
            element->next = tree.at(source).next;
            tree.at(source).next = element;
            tree.at(ptr->vertex).parent = source;
            t = dfs_visit(ptr->vertex,tree,adj,t+1);
            /*dfs_visit(ptr->vertex,tree,adj,t)*/
        }
        ptr = ptr->next;
    }
    /*no return*/
    tree.at(source).f = t;
    return t;
}


std::vector<node> dfs(std::vector<node> adj){
    std::vector<node> deep_tree = adj;
    for(auto &itr: deep_tree){ /*testing this, but i don't like it*/
        itr.color = false;
        itr.next = nullptr;
    }
    int t = 0;
    for(int i = 0; i < deep_tree.size(); i++){
        if(!deep_tree.at(i).color){
            t = dfs_visit(i,deep_tree,adj,t);
            t++;
        }
    }

    return deep_tree;
    
}

/*
22.3-7
i may need gray color here thinking
or initialize final time to something else
*/

std::vector<node> dfs_iteractive(std::vector<node> adj){
    std::vector<node> deep_tree = adj;
    for(uint i = 0; i < deep_tree.size(); i++){
        deep_tree.at(i).color = false;
        deep_tree.at(i).next = nullptr;
        deep_tree.at(i).f = -1;
    }

    std::stack<int> next;
    uint t = 0;
    for(uint i = 0; i < deep_tree.size(); i++){
        if(!deep_tree.at(i).color){
            next.push(i);

            while(!next.empty()){
                int num = next.top();
                if(deep_tree.at(num).color){
                    if(deep_tree.at(num).f == -1){
                        deep_tree.at(num).f = t;
                        t++;
                    }
                    next.pop();
                }

                else{
                    deep_tree.at(num).color = true;
                    deep_tree.at(num).d = t;
                    node* ptr = adj.at(num).next;

                    while(ptr!= nullptr){
                        if(!deep_tree.at(ptr->vertex).color){
                            next.push(ptr->vertex);
                        }
                        ptr = ptr->next;
                    }
                    t++;
                }

            }
        }
    }

    return deep_tree;
}


/*22.3-13
if i'm not mistaken, do a dfs, expect to find only white verteces
*/



/*chapter 22.4*/

void topological_recursion(uint i,std::vector<node> &adj, node* &list_head){
    adj.at(i).color = true;
    
    node* ptr = adj.at(i).next;
    while(ptr!=nullptr){
        if(!adj.at(ptr->vertex).color){ /*in a dag this is always true, as there are no cycles*/
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
    /*this is the smae as dfs but we keep track of finished nodes*/
    node* list_head  = new node;
    
    /*i don't really need to keep track of time here, only the order each node is finished*/
    /*as so i will not create a new list, on the assumption we have visited the nodes*/
    /*adj was called using the copy_constructor*/
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

/*this does too many recursions, and redo too many paths, we must keep track of how many
paths there are between a and b*/
uint paths(std::vector<node> adj, std::vector<uint> pos,std::vector<uint> &numbers ,uint a, uint b){
    if(numbers.at(a) != UINT_MAX) return numbers.at(a);
    
    if(pos.at(a) > pos.at(b)) numbers.at(a) = 0;
    
    else if(a == b) numbers.at(a) = 1;
    
    else{
        node* ptr = adj.at(a).next;

        while(ptr!=nullptr){
            numbers.at(a) += paths(adj,pos,numbers,ptr->vertex,b);
            ptr = ptr->next;
        }
    }

    return numbers.at(a);
}

/*22.4-2*/
/*explanation on notebook, i really liekd this one*/
uint count_paths(std::vector<node> adj, uint a, uint b){
    node* sort = topological_sort(adj);
    std::vector<uint> position(adj.size());
    std::vector<uint> numbers(adj.size(),UINT32_MAX);

    node* ptr = sort;
    uint j = 0;

    while(ptr!=nullptr){
        position.at(ptr->vertex) = j;
        j++;
        ptr = ptr->next;
    }

    paths(adj,position,numbers,a,b);
    return numbers.at(a);
}

/*22.4-5
done by Claudson in class, implemented before*/

/*22.5
strongly connected components*/

/*using reference to avoid unnecessary mem locking*/
std::vector<node> transpose_graph(std::vector<node> &adj){
    std::vector<node> transpose(adj.size());

    for(uint i = 0; i < adj.size(); i++){
        node* ptr = adj.at(i).next;
        while(ptr!=nullptr){
            node* t_edge = new node;
            t_edge->vertex = i;
            t_edge->next = transpose.at(ptr->vertex).next;
            transpose.at(ptr->vertex).next = t_edge;

            ptr = ptr->next;
        }
    }
    return transpose;
}

std::vector<node> strongly_connected(std::vector<node> adj){
    node* list = topological_sort(adj);
    node* ptr = list;

    std::vector<node> forest(adj.size());
    
    for(uint i = 0; i < forest.size(); i++){
        forest.at(i).color = false;
        forest.at(i).next = nullptr;
    }
    
    std::vector<node> transpose = transpose_graph(adj);

    int t = 0;
    while(ptr != nullptr){
        if(!forest.at(ptr->vertex).color){
            t = dfs_visit(ptr->vertex,forest,transpose,t);
            t++;
        }
    }

    return forest; /*this is a forest*/
    
}

/*22.5-5*/
/*i'll make an auxialiary dfs, one such I just know which component each vertex belongs to*/

void component_graph_aux(uint source, uint &set,std::vector<node> &adj, std::vector<uint> &trees){
    adj.at(source).color = true;
    trees.at(source) = set;

    node* ptr = adj.at(source).next;
    while(ptr!=nullptr){
        if(!adj.at(ptr->vertex).color){
            component_graph_aux(ptr->vertex,set,adj,trees);
        }
    }
}

std::vector<node> component_graph(std::vector<node> adj){
    node* list = topological_sort(adj);
    std::vector<node> transpose = transpose_graph(adj);
    for(uint i = 0; i < transpose.size(); i++){
        transpose.at(i).color = false;
    }

    /*instead of making a forest, we just need to know to which component each belongs*/
    node* ptr = list;
    std::vector<uint> sets(adj.size(),-1);
    uint j = 0;
    while(ptr!=nullptr){
        if(!transpose.at(ptr->vertex).color){
            component_graph_aux(ptr->vertex,j,transpose, sets);
            j++;
        }
        ptr = ptr->next;
    }

    /*this is a bit dumb, as i'm not telling which vertices belogn to which components*/

    /*create component graph*/
    std::vector<node> scc(j);

    /*go thru each edge, adding it to scc if it doesn't connect same components*/
    for(uint i = 0; i < adj.size(); i++){
        node* edges = adj.at(i).next;
        while(edges != nullptr){
            if(sets.at(i) != sets.at(edges->vertex)){ /*edge does not connect same strong connected component*/
                /*create new edge in scc graph*/
                node* connection = new node;
                connection->vertex = sets.at(edges->vertex);
                connection->next = scc.at(sets.at(i)).next;
                scc.at(sets.at(i)).next = connection;
            }

            edges = edges->next;
        }
    }

    /*remove unnecessary edges
    this here could be optimized, but i'm lazy lol*/
    return simplified_graph(scc);
}

/*22.5-6
do almost the same as before, but make cycles out of strongly components,
connect components as needed later*/

/*22.5-7 this one is a bit smarter, couldn't really solve myself
get the component set, topological it, because it's a dag. We need that every component is connected to the one after
suppose Ck isn't connected to Ck+1, then there's no path from Ck to Ck+1 and certainly no path from Ck+1 to Ck. So it couldn't be
semi connected
*/

bool semiconnected(std::vector<node> &adj){
    std::vector<node> component = component_graph(adj);
    node* ptr = topological_sort(component);
    while(ptr->next != nullptr){
        node* edges = component.at(ptr->vertex).next;
        bool found = false;
        while(edges != nullptr){
            if(edges->vertex == ptr->next->vertex){
                found = true;
                break;
            }
            edges = edges->next;
        }
        if(!found) return false;
        ptr = ptr->next;
    }
    return true;
}
