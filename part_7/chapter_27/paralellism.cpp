#include <bits/stdc++.h>

using namespace std;

int p_fib(int n){
    if(n <= 1) return n;

    auto x = std::async(p_fib,n-1);
    auto y = p_fib(n-2);
    
    // x.wait();
    //uneeded as x.get() awaits if not returned
    return y + x.get();
}

void find_value(vector<vector<int>> &matrix, vector<int> &x,int line,vector<int> &answer){
    answer.at(line) = 0;
    for(uint i = 0; i < x.size(); i++){
        answer.at(i) += matrix.at(line).at(i) * x.at(i);
    }
}

vector<int> matrix_vec(vector<vector<int>> &matrix, vector<int> &x){

    vector<thread> threads;
    vector<int> resp(x.size());
    for(int i = 0; i < x.size(); i++){
        threads.emplace_back(find_value,matrix,x,i,resp);
    }

    for(auto& thread : threads){
        thread.join();
    }

    return resp;
}


/*
MAT-VEC-MAIN-LOOP(A,x,y,n,i,i')
    if i == i'
        for j = 1 to n
            yi = yi + aij*xj
    else mid = (i + i')/2
    spawn mat-vec-main-loop(A,x,y,n,i,mid)
    mat-vec-main-loop(A,x,y,n,mid+1,i')
    sync
*/

int main(void){
    p_fib(10);
    return 0;
}