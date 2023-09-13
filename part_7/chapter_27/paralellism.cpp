#include <bits/stdc++.h>

int p_fib(int n){
    if(n <= 1) return n;

    auto x = std::async(p_fib,n-1);
    auto y = p_fib(n-2);
    
    // x.wait();
    //uneeded as x.get() awaits if not returned
    return y + x.get();
}

int main(void){
    p_fib(10);
    return 0;
}