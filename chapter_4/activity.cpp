#include <bits/stdc++.h>

using namespace std;
struct answer{
    vector<vector<int>> a;
    vector<vector<int>> r;
};

answer dynamic_activity(std::vector<int> start, std::vector<int> finish){
    int tam = start.size();
    vector<vector<int>> a(tam + 2);
    vector<vector<int>> r(tam + 2);
    for(int i = 0; i < tam+2; i++){
        a.at(i).resize(tam+2);
        r.at(i).resize(tam+2);
    }

    vector<int> si = {-1};
    vector<int> fi = {0};
    for(int i = 0; i < tam; i++){
        si.push_back(start.at(i));
        fi.push_back(finish.at(i));
    }
    si.push_back(INT_MAX - 1);
    fi.push_back(INT_MAX);



    for(int i = 1; i < tam + 2; i++){
        for(int lin = 0; lin < tam + 2 - i; lin++){
            int col = i + lin;
            /*estou contando do 1,  0 é start = 0, tam + 1 é fim = infty*/
            a.at(lin).at(col) = 0;
            vector<int> set;
            for(int m = lin + 1; m < col; m++){ 
                if(fi.at(lin) <= si.at(m) && fi.at(m) <= si.at(col)){
                    set.push_back(m);
                }
            }

            for(size_t k = 0; k < set.size(); k++){
                int sum = a.at(lin).at(set.at(k)) + a.at(set.at(k)).at(col) + 1;
                if(sum > a.at(lin).at(col)){
                    a.at(lin).at(col) = sum;
                    r.at(lin).at(col) = set.at(k);
                }
            }
        }
    }

    answer p;
    p.a = a;
    p.r = r;
    return p;
}

/*
1 2 3 4
# 1 2 3
# # 1 2
# # # 1

*/

void retrieve_answer(answer &p, int i, int j, vector<int> &sequence){
    int m = p.r.at(i).at(j);
    if(m == 0) return;

    retrieve_answer(p,i,m,sequence);
    sequence.push_back(m-1);
    retrieve_answer(p,m,j,sequence);
}

void recursive_activity(std::vector<int> start, std::vector<int> finish, int k, std::vector<int> &answer){
    int tam = start.size();
    int m = k + 1;

    while(m < tam && start.at(m) < finish.at(k)){
        m++;
    }

    if(m < tam){
        answer.push_back(m);
        recursive_activity(start,finish,m,answer);
    }
}

std::vector<int> rec_activity(vector<int> start, vector<int> finish){
    std::vector<int> answer;
    answer.push_back(0);
    recursive_activity(start,finish,0,answer);
    return answer;
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


int main(void){

    vector<int> si = {1,3,0,5,3,5,6,8,8,2,12};
    vector<int> fi = {4,5,6,7,9,9,10,11,12,14,16};
    int tam = fi.size();


    vector<int> rec = rec_activity(si,fi);
    std::cout << "recursive" << std::endl;
    for(size_t i = 0; i < rec.size(); i++){
        std::cout << rec.at(i) << " ";
    }
    std::cout << std::endl;

    vector<int> iter = iterative_activity(si,fi);
    std::cout << "iterative" << std::endl;
    for(size_t i = 0; i < iter.size(); i++){
        std::cout << iter.at(i) << " ";
    }
    std::cout << std::endl;

    std::cout << "sequence ? " << std::endl;
    answer dynamic = dynamic_activity(si,fi);
    vector<int> resp;
    retrieve_answer(dynamic,0,tam+1,resp);
    for(size_t i = 0; i < resp.size(); i++){
        std::cout << resp.at(i) << " ";
    }
    std::cout<<std::endl;
    
    return 0;
}
