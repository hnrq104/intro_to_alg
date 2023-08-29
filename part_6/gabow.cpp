#include<bits/stdc++.h>

/*24.4*/

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


/* i really don't want to test this*/
std::vector<uint> gabow_scaling(std::vector<node> &g, uint source, uint E, uint W){ /*E is just the amount of edges, we could count but i'm lazy*/

    std::vector<std::queue<uint>> order_of_elements(E+1);
    uint mask = (1<<31);
    uint most_significant_bit = 32;
    while(mask > (mask-W)){
        mask = mask >> 1;
        most_significant_bit--;
    }

    std::vector<uint> shortest_path_i(g.size(),0); /*this will hold delta i-1*/
    
    for(uint stage = 1; stage <= most_significant_bit; stage++){ /* variable "i" in the question*/

        std::vector<uint> shortest_reweighted(g.size());
        std::vector<bool> already_removed(g.size());

        uint number_in_tree = 0; /*only the source vertex*/
        uint current_distance = 0;
        order_of_elements.at(0).push(source);
        /*we initialize this every stage*/


        while(number_in_tree != g.size() && current_distance <= E){
            while(!order_of_elements.at(current_distance).empty()){
                uint element = order_of_elements.at(current_distance).front();
                order_of_elements.at(current_distance).pop();

                if(already_removed.at(element)) continue;/*element was already considered*/

                shortest_reweighted.at(element) = current_distance;
                already_removed.at(element) = true;
                
                node* edge_list = g.at(element).next;
                while(edge_list!=nullptr){
                    uint weight_i = (edge_list->f)>>(most_significant_bit - stage);  /*this will yield wi*/
                    uint reweighted = weight_i + 2*shortest_path_i.at(element) - 2*shortest_path_i.at(edge_list->vertex);
                    order_of_elements.at(current_distance + reweighted).push(edge_list->vertex);

                    edge_list = edge_list->next;
                }
            }
            current_distance++;
        }

        for(uint i = 0;i < shortest_path_i.size();i++){
            shortest_path_i.at(i) = shortest_reweighted.at(i) - 2*shortest_path_i.at(i);
        }
    }

    return shortest_path_i;
}

int main(void){
    uint i = 1;
    std::cout << std::hex << (i<<31) - ((i-2)) << std::endl;
    std::cout << std::hex  <<  (i<<31) << std::endl;
    std::cout << std::hex  << i - 2 << std::endl;


    uint W = 25;

    uint mask = (1<<31);
    uint most_significant_bit = 32;
    while(mask > (mask-W)){
        mask = mask >> 1;
        most_significant_bit--;
    }

    std::cout << std::hex <<  mask << std::endl;
    std::cout << most_significant_bit << std::endl;

    
    

    return 0;
}