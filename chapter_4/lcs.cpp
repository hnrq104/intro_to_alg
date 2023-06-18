#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> lcs_lenght(vector<int> a, vector<int> b){
    int m = a.size();
    int n = b.size();

    vector<vector<int>> c;
    c.resize(m+1);

    for(int i = 0; i <= m; i++){
        c.at(i).resize(n+1);
        c.at(i).at(0) = 0;
    }

    for(int i = 0; i < n + 1; i++) c.at(0).at(i) = 0;

    for(int i = 1; i < m + 1; i++){
        for(int j = 1; j < n + 1; j++){
            if(a.at(i - 1) == b.at(j - 1)){
                c.at(i).at(j) = c.at(i-1).at(j-1) + 1;
            }
            else c.at(i).at(j) = max(c.at(i - 1).at(j),c.at(i).at(j-1));
            
        }
    }

    return c;
}



int lcs_inside(int i, int j,vector<vector<int>> &c, vector<int> a, vector<int> b){
    if(c.at(i).at(j) != -1) return c.at(i).at(j);

    int v = 0;
    if(i == 0 || j == 0){
        c.at(i).at(j) = 0;
        return v;
    }

    if(a.at(i-1) == b.at(j-1)){
        v = lcs_inside(i-1,j-1,c,a,b) + 1;
        c.at(i).at(j) = v;
        return v;
    }

    v = max(lcs_inside(i-1,j,c,a,b),lcs_inside(i,j-1,c,a,b));
    c.at(i).at(j) = v;
    return v;
}

vector<vector<int>> lcs_memo(vector<int> a, vector<int> b){
    int m = a.size();
    int n = b.size();
    vector<vector<int>> c(m+1);
    
    for(int i = 0; i < m+1; i++){
        vector<int> x(n+1,-1);
        c.at(i) = x;
    }

    lcs_inside(m,n,c,a,b); 
    return c;
}

void print_result(int i, int j, vector<int> a, vector<vector<int>> c){
    if(i == 0 || j == 0){
        return;
    }

    if(c.at(i).at(j) == c.at(i-1).at(j-1) + 1){
        print_result(i-1,j-1,a,c);
        std::cout << a.at(i-1);
        return;
    }

    if(c.at(i).at(j) == c.at(i-1).at(j)){
        print_result(i-1,j,a,c);
        return;
    }

    if(c.at(i).at(j) == c.at(i).at(j-1)){
        print_result(i,j-1,a,c);
        return;
    }

}


int main(void){
    vector<int> a = {1,0,0,1,0,1,0,1};
    vector<int> b = {0,1,0,1,1,0,1,1,0};

    vector<vector<int>> c = lcs_lenght(a,b);
    vector<vector<int>> d = lcs_memo(a,b);


    print_result(a.size(),b.size(),a,c);
    std::cout << std::endl;

    print_result(a.size(),b.size(),a,d);
    std::cout << std::endl;

    
    return 0;
}