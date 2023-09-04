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

                Lnew.at(i).at(j) = min(Lnew.at(i).at(j), L.at(i).at(k) + W.at(k).at(j));
                /*if Lnew changes -> P.at(i).at(j) = k*/
            }
        }
    }

    return Lnew;
}

template<typename T>
void print_matrix(vector<vector<T>> &L){
    for(vector<T> v : L){
        for(T d : v){
            if(d == DBL_MAX){
                cout << "infty" << " ";
            }
            else cout << d << " ";
        }
        cout << endl;
    } 
}

vector<vector<double>> slow_all_pairs_shortest_paths(vector<vector<double>> W){
    int n = W.size();
    vector<vector<double>> L = W;

    for(int m = 2; m < n; m++){
        L = extend_shortest_paths(L,W);
        
        /*printa a matriz*/
        /*
        cout << "L" << m << " = " << endl;
        print_matrix(L);
        cout << endl;
        */

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

        /*
        cout << "L" << m << " = " << endl;
        print_matrix(L);
        cout << endl;
        */
    }

    return L;
}

/*25.1-9 check if diagonals changed*/

/*25.1-10 first time diagonals changed, go back in cycle*/



int main(void){

    int n = 5;
    vector<vector<double>> Lnew(n,vector<double>(n,DBL_MAX)); /*initialize L' with all values at infinity*/

    vector<vector<double>> W = {
        {0,DBL_MAX,DBL_MAX,DBL_MAX,-1,DBL_MAX},
        {1,0,DBL_MAX,2,DBL_MAX,DBL_MAX},
        {DBL_MAX,2,0,DBL_MAX,DBL_MAX,-8},
        {-4,DBL_MAX,DBL_MAX,0,3,DBL_MAX},
        {DBL_MAX,7,DBL_MAX,DBL_MAX,0,DBL_MAX},
        {DBL_MAX,5,10,DBL_MAX,DBL_MAX,0}
    };

    cout << "ORIGINAL WEIGHT MATRIX : " << endl;
    for(vector<double> v : W){
        for(double d : v){
            cout << d << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "SLOW ALL PAIRS SHORTEST PATH ITERATIONS : " << endl; 
    slow_all_pairs_shortest_paths(W);
    cout<<endl;

    cout << "FASTER ALL PAIRS SHORTEST PATH ITERATIONS : " << endl; 
    vector<vector<double>> complete = faster_all_pairs_shortest_path(W);
    print_matrix(complete);
    cout<<endl;
    

    cout << (-2.0 + -1.0 == -3.0) << endl; 
    return 0;


}