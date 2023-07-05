#include <bits/stdc++.h>

struct task{
    int id;
    int weight;
    int deadline;
};

bool compare(task a, task b){
    return a.weight>b.weight;
}

bool ordenate(task a, task b){
    return a.id < b.id;
}

std::vector<task> greedy(std::vector<task> a){
    sort(a.begin(),a.end(),compare);
    std::vector<task> sol;
    for(uint i = 0; i < a.size(); i++){
        bool ind = true;
        for(uint j = 0; j < sol.size(); j++){
            if(a.at(i).deadline == sol.at(j).deadline){
                ind = false;
                break;
            }
        }
        if(ind) sol.push_back(a.at(i));
    }
    std::sort(sol.begin(),sol.end(), ordenate);
    return sol;
    
}


int main(void){
    std::vector<task> v(7);
    std::srand(std::time(nullptr));
    for(uint i = 0; i < v.size(); i++){
        v.at(i).id = i;
        v.at(i).deadline = std::rand()%6 + 1;
        v.at(i).weight = std::rand()%100 + 1;
    }

    std::cout << "Initialized vector" << std::endl; 
    for(uint i = 0; i < v.size(); i++){
        std::cout << v.at(i).id << " ";
        std::cout << v.at(i).deadline << " ";
        std::cout << v.at(i).weight << std::endl;
        
    }

    std::cout << "Sorting vector" << std::endl;
    std::sort(v.begin(),v.end(),compare);
    for(uint i = 0; i < v.size(); i++){
        std::cout << v.at(i).id << " ";
        std::cout << v.at(i).deadline << " ";
        std::cout << v.at(i).weight << std::endl;
        
    }

    std::vector<task> sol = greedy(v);
    std::cout << "Solution" << std::endl;
        for(uint i = 0; i < sol.size(); i++){
        std::cout << sol.at(i).id << " ";
        std::cout << sol.at(i).deadline << " ";
        std::cout << sol.at(i).weight << std::endl;
        
    }

    return 0;
}   