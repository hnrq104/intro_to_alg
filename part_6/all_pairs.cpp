#include <bits/stdc++.h>

/*i really should start using python now, but i began with c++. so with c++ i will stay*/

using namespace std;

void print_all_pairs_shortest_path(vector<vector<int>> PI_MATRIX, int i, int j){
    if(i == j){
        cout<< i << " ";
    }

    else if(PI_MATRIX.at(i).at(j) == -1){
        cout << "no path from " << i << " to " << j << "exists ";
    }

    else{
        print_all_pairs_shortest_path(PI_MATRIX,i,PI_MATRIX.at(i).at(j));
        cout << j << " ";
    }
}

vector<vector<double>> extend_shortest_paths(vector<vector<double>> &L, vector<vector<double>> &W){
    int n = L.size();
    vector<vector<double>> Lnew(n,vector<double>(n,DBL_MAX)); /*initialize L' with all values at infinity*/

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                Lnew.at(i).at(j) = min(Lnew.at(i).at(j), L.at(i).at(k) + W.at(i).at(k));
            }
        }
    }

    return Lnew;
}

vector<vector<double>> slow_all_pairs_shortest_paths(vector<vector<double>> W){
    int n = W.size();
    vector<vector<double>> L = W;

    for(int m = 2; m < n; m++){
        L = extend_shortest_paths(L,W);
    }

    return L;
}

vector<vector<double>> faster_all_pairs_shortest_path(vector<vector<double>> W){
    int n = W.size();
    vector<vector<double>> L = W;
    int m = 1;
    while(m < n-1){
        L = extend_shortest_paths(L,L);
        m *= 2;
    }

    return L;
}


int main(void){

    int n = 5;
    vector<vector<double>> Lnew(n,vector<double>(n,DBL_MAX)); /*initialize L' with all values at infinity*/

    for(vector<double> v : Lnew){
        for(double d : v){
            cout << d << " ";
        }
        cout << endl;
    }
    
    return 0;


}