#include <bits/stdc++.h>

using namespace std;
int dynamic_activity(std::vector<int> start, std::vector<int> finish){
    int tam = start.size();
    vector<vector<int>> a(tam);
    for(int i = 0; i < tam; i++){
        a.at(i).resize(tam);
        a.at(i).at(i) = 0;
    }

    for(int i = 1; i < tam; i++){
        for(int j = 0; j < tam - i; j++){
            int col = j + i;
            vector<int> s;
            a.at(j).at(col) = 0; 

            /*há formas mais espertas de produzir o s*/
            for(int k = 0; k < tam; k++){
                if(start.at(k) >= finish.at(j) && finish.at(k) < start.at(col)){
                    s.push_back(k);
                }
            }
            /*mas como esse algoritmo é greedy, deixa isso aqui só de sacanagem*/

            for(size_t k = 0; k < s.size(); k++){
                int sum = a.at(j).at(k) + a.at(k).at(col);
                if(sum > a.at(j).at(col)){
                    a.at(j).at(col) = sum;
                    /*poderia salvar solução mas novamente, desnecessário*/
                }
            }

            a.at(j).at(col)++;

        }
    }

    return a.at(0).at(tam - 1);
}

void recursive_activity(std::vector<int> start, std::vector<int> finish, int k, std::vector<int> &answer){
    int tam = start.size();
    int m = k + 1;

    while(m < start.size() && start.at(m) < finish.at(k)){
        m++;
    }

    if(m < start.size()){
        answer.push_back(m);
        recursive_activity(start,finish,m,answer);
    }
}

std::vector<int> iterative_activity(std::vector<int> start, std::vector<int> finish){
    std::vector<int> answer;
    answer.push_back(0);

    int k = 0;
    int tam = start.size();
    for(int i = 1; i < tam; i++){
        if(start.at(i) >= finish.at(k)){
            answer.push_back(i);
            k = i;
        }
    }

    return answer;
}