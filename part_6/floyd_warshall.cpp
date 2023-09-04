#include <bits/stdc++.h>

using namespace std;


vector<vector<double>> floyd_warshall(vector<vector<double>> W){
    int n = W.size();

    vector<vector<double>> D = W;
    vector<vector<double>> AUX(n,vector<double>(n)); /*there's a smarter way to do this with pointers
    which may reduce significantly time at least in half, (don't copy aux over to D, only change the pointer referring to D)*/
    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                AUX.at(i).at(j) = min(D.at(i).at(j),D.at(i).at(k) + D.at(k).at(j));
            }
        }
        D = AUX; /*this is slow*/
    }

    return D;
}



template<typename T>
void print_matrix(vector<vector<T>> L){
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

/*25.2-1*/
vector<vector<double>> floyd_warshall_printing(vector<vector<double>> W){
    int n = W.size();

    vector<vector<double>> D = W;
    vector<vector<double>> AUX(n,vector<double>(n)); /*there's a smarter way to do this with pointers
    which may reduce significantly time at least in half, (don't copy aux over to D, only change the pointer referring to D)*/

    vector<vector<double>>* D_ptr = &D;
    vector<vector<double>>* AUX_ptr = &AUX; 

    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                AUX_ptr->at(i).at(j) = min(D_ptr->at(i).at(j),D_ptr->at(i).at(k) + D_ptr->at(k).at(j));
            }
        }
        vector<vector<double>>* temp = D_ptr; 
        D_ptr = AUX_ptr;
        AUX_ptr = temp;

        cout <<"K = " << k << endl;
        print_matrix(*D_ptr);
        cout << endl;
    }

    return *D_ptr;
}

/*25.2-2*/

vector<vector<bool>> transitive_extend(vector<vector<bool>> &T, vector<vector<bool>> &W){
    int n = T.size();
    vector<vector<bool>> Tnew(n,vector<bool>(n,false)); /*initialize L' with all values at infinity*/

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){

                Tnew.at(i).at(j) = Tnew.at(i).at(j) || (T.at(i).at(k) && W.at(k).at(j));
                /*if Lnew changes -> P.at(i).at(j) = k*/
            }
        }
    }

    return Tnew;
}

vector<vector<bool>> faster_all_pairs_shortest_path(vector<vector<double>> W){
    int n = W.size();
    int m = 1;

    vector<vector<bool>> T;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i == j || W.at(i).at(j) != DBL_MAX){
                T.at(i).at(j) = true;
            }
            else T.at(i).at(j) = false;
        }
    }

    /*I should do the fast method*/
    while(m < n-1){
        T = transitive_extend(T,T);
        m *= 2;
    }

    return T;
}


/*25.2-3 Floyd Marshall with Predecessor*/
vector<vector<double>> floyd_warshall_predecessor(vector<vector<double>> W, vector<vector<int>> &P){ 
    int n = W.size();

    vector<vector<double>> D = W;
    vector<vector<double>> AUX(n,vector<double>(n)); /*there's a smarter way to do this with pointers
    which may reduce significantly time at least in half, (don't copy aux over to D, only change the pointer referring to D)*/

    vector<vector<double>>* D_ptr = &D;
    vector<vector<double>>* AUX_ptr = &AUX;

    vector<vector<int>> PREDECESSOR_AUX(W.size(),vector<int>(W.size())); /*PI(O)*/
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i == j || W.at(i).at(j) == DBL_MAX) PREDECESSOR_AUX.at(i).at(j) = -1; //NIL;
            else PREDECESSOR_AUX.at(i).at(j) = i;
        }
    }

    vector<vector<int>>* P_ptr = &PREDECESSOR_AUX;
    vector<vector<int>>* P_AUX_ptr = &P;

    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                AUX_ptr->at(i).at(j) = min(D_ptr->at(i).at(j),D_ptr->at(i).at(k) + D_ptr->at(k).at(j));
                /*calculate PI*/
                if(D_ptr->at(i).at(j) <= D_ptr->at(i).at(k) + D_ptr->at(k).at(j)){
                    P_AUX_ptr->at(i).at(j) = P_ptr->at(i).at(j);
                }
                else{
                    P_AUX_ptr->at(i).at(j) = P_ptr->at(k).at(j);
                }
            }
        }
        vector<vector<double>>* temp = D_ptr; 
        D_ptr = AUX_ptr;
        AUX_ptr = temp;

        vector<vector<int>>* P_tmp = P_ptr;
        P_ptr = P_AUX_ptr;
        P_AUX_ptr = P_tmp;
    }

    if(P_ptr != &P){
        P = *P_ptr;
    }

    return *D_ptr;
}

/*TRUE FLOYDWARSHALL WITHOUT ALL THE POINTER stuff, it really didn't matter, i should have thought that*/

vector<vector<double>> F_W(vector<vector<double>> &G){
    int n = G.size();
    vector<vector<double>> D = G;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                D.at(i).at(j) = min(D.at(i).at(j), D.at(i).at(k) + D.at(k).at(j));
            }
        }
    }
    return D;
}


vector<vector<double>> F_W(vector<vector<double>> &G, vector<vector<int>> &phi){
    int n = G.size();
    vector<vector<double>> D = G;
    vector<vector<int>> p(G.size(), vector<int>(G.size()));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
            if(D.at(i).at(k) + D.at(k).at(j) < D.at(i).at(j)){
                p.at(i).at(j) = k;
                D.at(i).at(j) = D.at(i).at(k) + D.at(k).at(j);
            } 

            }
        }
    }

    phi = p;
    return D;
}

int main(void){
    /*graph of figrue 25.1*/
    vector<vector<double>> W = {
        {0,3,8,DBL_MAX,-4},
        {DBL_MAX,0,DBL_MAX,1,7},
        {DBL_MAX,4,0,DBL_MAX,DBL_MAX},
        {2,DBL_MAX,-5,0,DBL_MAX},
        {DBL_MAX,DBL_MAX,DBL_MAX,6,0}
    };

    // print_matrix(floyd_warshall(W));

    /*25.2-1*/
    //floyd_warshall_printing(W);
    floyd_warshall(W);


    return 0;
}