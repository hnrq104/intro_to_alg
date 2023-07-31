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


int main(void){
}