#include <bits/stdc++.h>
using namespace std;
/*
vector<vector<int>> matrix_multiply(vector<vector<int>> a, vector<vector<int>> b){
    if(a.at(0).size() != b.size()) throw invalid_argument("matrices cannot be multiplied");
    
    vector<vector<int>> c(a.size());
    for(int i = 0; i < c.size(); i++){
        vector<int> tmp(b.at(0).size());
        c.at(i) = tmp;
    }


    for(int i = 0; i < c.size(); i++){
        for(int j = 0; j < c.at(0).size(); j++){
            int soma = 0;
            for(int k = 0; k < a.at(0).size(); k++){
                soma += a.at(i).at(k) + b.at(k).at(j);
            }
            c.at(i).at(j) = soma;
        }
    }

    return c;

}
*/
/*
n col a = num lin b
a11 a12 a13 a14
a21 a22 a23 a24
a31 a32 a33 a34

b11 b12 b13 b14 
b21 b22 b23 b24
b31 b23 b33 b34
b41 b42 b43 b44

r = n lin a x n col b
*/

/*
m[i,j] = {
    0 se i = j
    min k= i -> j-1 (m[i,k] + m[k+1,j] + pi*pk*pj)
}
*/


struct ret{
    vector<vector<int>> table;
    vector<vector<int>> answer;
};

ret matrix_associaton(vector<int> p){
    int tam = p.size()-1;

    ret r;
    r.table.resize(tam);
    r.answer.resize(tam);
    for(int i = 0; i < tam; i++){
        r.table.at(i).resize(tam);
        r.answer.at(i).resize(tam);
    }

    for(int i = 0; i < tam; i++){
        r.table.at(i).at(i) = 0;
    }

    for(int i = 1; i < tam; i++){
        for(int j = 0; j < tam - i; j++){
            //muito mais legivel com min
            int min = INT32_MAX;
            //linha = j;
            //col = i + j;
            for(int k = j + 1; k <= i + j; k++){
                int custo = r.table.at(j).at(k-1) + r.table.at(k).at(i+j) + p.at(j)*p.at(k)*p.at(i + j + 1);
                if(custo < min){
                    min = custo;
                    r.answer.at(j).at(i+j) = k;
                }
            }
            r.table.at(j).at(i+j) = min;
        }
    }

    return r;
}

void printa_assoc(vector<vector<int>> sol, int i, int j){
    if(i == j){
        std::cout<<"A"<<i;
        return;
    }

    std::cout << "(";
    int k = sol.at(i).at(j);
    printa_assoc(sol,i,k-1);
    printa_assoc(sol,k,j);
    std::cout << ")";

    
}

int main(void){
    /*
    //exemplo livro

    vector<int> p = {30,35,15,5,10,20,25};
    ret r = matrix_associaton(p);
    std::cout << "resp = " << r.table.at(0).at(5) << std::endl;

    printa_assoc(r.answer,0,5);
    std::cout << std::endl;
    */

    /*exercicio 15.2-1*/
    vector<int> e = {5,10,3,12,5,50,6};
    ret s = matrix_associaton(e);
    std::cout << "melhor custo = " << s.table.at(0).at(e.size() - 2) << std::endl;
    printa_assoc(s.answer,0,e.size() - 2);
    std::cout << std::endl;

    

    return 0;
}


