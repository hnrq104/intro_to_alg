#include <bits/stdc++.h>

using namespace std;

struct ans{
    vector<vector<float>> costs;
    vector<vector<int>> root;
};

ans construct_optimal_bst(vector<float> p, vector<float> q){
    ans a;
    int tam = q.size();
    a.costs.resize(tam);
    a.root.resize(tam);

    vector<vector<float>> w(tam);

    for(int i = 0; i < tam; i++){
        a.costs.at(i).resize(tam);
        a.root.at(i).resize(tam);
        w.at(i).resize(tam);

        a.costs.at(i).at(i) = q.at(i);
        a.root.at(i).at(i) = i;
        w.at(i).at(i) = q.at(i);
    }
    // std::cout << "oi HENRIQUE " << std::endl;

    for(int i = 1; i < tam; i++){
        for(int j = 0; j < tam - i; j++){
            int col = i + j;

            w.at(j).at(col) = w.at(j).at(col-1) + p.at(col - 1) + q.at(col);
            a.costs.at(j).at(col) = INT32_MAX;

            for(int k = a.root.at(j).at(col-1); k <= a.root.at(j+1).at(col) && k < col; k++){
                float sum = a.costs.at(j).at(k) + a.costs.at(k+1).at(col);
                if(sum < a.costs.at(j).at(col)){
                    a.costs.at(j).at(col) = sum;
                    a.root.at(j).at(col) = k;
                }
            }
            a.costs.at(j).at(col) += w.at(j).at(col);
        }
    }

    return a;
}

void print_optimal_bst(vector<vector<int>> root, int last,int i, int j){
    if(i == j){
        if(i < last){
            std::cout << "d" << i << "é filho esquerdo de " << last<<std::endl;
        }
        else{
            std::cout << "d" << i << "é filho direito de " << last<<std::endl;
        }
        return;
    }
    int k = root.at(i).at(j);
    if(last == -1){
        std::cout << k << " é a raiz" << std::endl;
    }

    else if(root.at(i).at(j) < last){
        std::cout << k << " é filho esquerdo de " << last <<std::endl;
    }

    else if(root.at(i).at(j) > last){
        std::cout << k << " é filho direito de " << last <<std::endl;
    }

    print_optimal_bst(root, k, i,k-1);
    print_optimal_bst(root, k, k,j);
}


int main(void){
    vector<float> pi = {0.15,0.10,0.05,0.10,0.20};
    vector<float> qi = {0.05,0.10,0.05,0.05,0.05,0.10};

    ans r = construct_optimal_bst(pi,qi);
    std::cout<<"costs" << std::endl;
    for(size_t i = 0; i < r.root.size(); i++){
        for(size_t j = i; j < r.root.size(); j++){
            std::cout << r.costs.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "roots" << std::endl;
    
    for(size_t i = 0; i < r.root.size(); i++){
        for(size_t j = i; j < r.root.size(); j++){
            std::cout << r.root.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }

    print_optimal_bst(r.root,-1,0,5);


    return 0;
}