#include <bits/stdc++.h>
using namespace std;

vector<double> lup_solve(vector<vector<double>> &L, vector<vector<double>> &U, vector<uint> pi, vector<double> b){
    uint n = L.size();
    vector<double> y(n);
    vector<double> x(n);
    for(uint i = 0; i < n; i++){
        y.at(i) = b.at(pi.at(i));
        for(uint j = 0; j < i; j++){
            y.at(i) -= L.at(i).at(j)*y.at(j); 
        }
    }

    for(int i = n-1; i >= 0; i--){
        x.at(i) = y.at(i);
        for(int j = i+1; j < n; j++){
            x.at(i) -= (U.at(i).at(j)*x.at(j));
        }
        x.at(i) = x.at(i)/U.at(i).at(i);
    }

    return x;
}


void lu_decomposition(vector<vector<double>> &A){
    uint n = A.size();

    for(uint k = 0; k < n; k++){
        for(uint i = k + 1; i < n; i++){
            A.at(i).at(k) = A.at(i).at(k)/A.at(k).at(k);
        }

        for(uint i = k + 1; i < n; i++){
            for(uint j = k + 1; j < n; j++){
                A.at(i).at(j) -= A.at(i).at(k)*A.at(k).at(j);
            }
        }
    }
}

void lup_decomposition(vector<vector<double>> &A, vector<uint> &pi){
    uint n = A.size();
    pi.resize(n);
    for(uint i = 0; i < n; i++){
        pi.at(i) = i;
    }

    for(uint k = 0; k < n; k++){
        uint p = k;
        for(uint i = k + 1; i < n; i++){
            if(abs(A.at(i).at(k)) > abs(A.at(p).at(k))){
                p = i;
            }
        }

        if(A.at(p).at(k) == 0){
            /*ERROR NON SINGULAR MATRIX*/
            return;
        }

        /*exchange permutation matrix*/
        uint tmp = pi.at(k);
        pi.at(k) = p;
        pi.at(p) = tmp;

        /*exchange rows*/
        for(uint i = 0; i < n; i++){
            double tmp = A.at(k).at(i);
            A.at(k).at(i) = A.at(p).at(i);
            A.at(p).at(i) = tmp;
        }

        for(uint i = k + 1; i < n; i++){
            A.at(i).at(k) = A.at(i).at(k)/A.at(k).at(k);
            for(uint j = k + 1; j < n; j++){
                A.at(i).at(j) -= A.at(i).at(k)*A.at(k).at(j);
            }
        }
    }   
}




int main(void){
    vector<vector<double>> L = {
        {1,0,0},
        {0.2,1,0},
        {0.6,0.5,1}
        };

    vector<vector<double>> U = {
        {5,6,3},
        {0,0.8,-0.6},
        {0,0,2.5}
        };
 

    vector<uint> P = {2,0,1};

    vector<double> b = {3,7,8};

    /*solve for lu*/
    std::cout << "lup_solve :" << std::endl;
    for(auto x : lup_solve(L,U,P,b)){
        std::cout << x << " ";
    }
    std::cout << std::endl;


    vector<vector<double>> a ={
        {2,3,1,5},
        {6,13,5,19},
        {2,19,10,23},
        {4,10,11,31}
    };

    lu_decomposition(a);
    std::cout << "lu decomposition :" << std::endl;
    for(auto x : a){
        for(auto y : x){
            std::cout  << y << " ";
        }
        std::cout << std::endl;
    }

    vector<vector<double>> o ={
        {2,0,2,0.6},
        {3,3,4,-2},
        {5,5,4,2},
        {-1,-2,3.4,-1}
    };

    /*28.1-3*/
    vector<vector<double>> k ={
        {1,5,4},
        {2,0,3},
        {5,8,2},
    };


    vector<uint> p(k.size());
    lup_decomposition(k,p);
    std::cout << "lup decomposition :" << std::endl;
    for(auto x : k){
        for(auto y : x){
            std::cout << y << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "lup_solve 28.1-3 :" << std::endl;
    vector<double> constants = {12,9,5};
    for(auto x : lup_solve(k,k,p,constants)){
        std::cout << x << " ";
    }
    std::cout << std::endl;

}
