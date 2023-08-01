#include <bits/stdc++.h>

struct node{
    uint vertex;
    node* next;

    node(){
        next = nullptr;
    }

};

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


/*exercise 22.1-4*/
/*similar to before, but we go into each edge looking for unconnected vertices*/

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
        }
    }

    return distances.at(num);
}
/*
int main(void){
    std::vector<int> a{1,2,3,4,5};
    for(auto &itr : a){ //interesting
        itr = 0;
        std::cout << itr << " ";

    }
    std::cout << std::endl;
    for(auto itr : a){
        std::cout << itr << " ";
    }
    return 0;
}
*/
