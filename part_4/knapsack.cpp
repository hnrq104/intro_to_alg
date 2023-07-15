#include <bits/stdc++.h>
using namespace std;

struct robbed_items{
    int weight;
    int cost;
};

int knapsack(int w, std::vector<robbed_items> v){
    int tam = v.size();
    vector<vector<int>> table(w+1);
    
    for(int i=0; i < w+1; i++){
        table.at(i).resize(tam + 1);
    }

    for(int i = 1; i < tam+1; i++){
        for(int j = 0; j < w + 1; j++){
            int cost = v.at(i-1).cost;
            int weight = v.at(i-1).weight;
            int maximum = table.at(j).at(i-1);
            if(j >= weight){
                maximum = max(maximum,table.at(j-weight).at(i-1) + cost);
            }
            table.at(j).at(i) = maximum;
        }
    }

    return table.at(w).at(tam);
}

int main(void){
    std::vector<robbed_items> r(5);
    srand(time(NULL));
    std::cout << "lista : \n";
    
    for(int i = 0; i < 5; i++){
        r.at(i).cost = rand()%8 + 1;
        r.at(i).weight = rand()%5 + 1;
        std::cout << r.at(i).cost << " ";
    }
    std::cout << "\n";
    for(int i = 0; i < 5; i++){
        std::cout << r.at(i).weight << " ";
    }
    std::cout << "\n";
    
    std::cout <<  knapsack(10,r) << std::endl;
    return 0;
}