#include <bits/stdc++.h>

int cut_rod(std::vector<int> prices, int n, std::vector<int> memo){
    if(memo.at(n) >= 0){
        return memo.at(n);
    }
    int pr = 0;
    for(int i = 1; i <= n; i++){
        int k = cut_rod(prices,n-i,memo) + prices.at(i);
        if(pr < k){
            pr = k;
        }
    }
    memo.at(n) = pr;
    return pr;
}

int memoized_cut_rod(std::vector<int> prices, int n){
    std::vector<int> r(n+1);
    /*initialize the n spaces*/
    for(int i = 0; i <= n; i++){
        r.at(i) = INT32_MIN;
    }

    return cut_rod(prices,n,r);
}

int bottom_up_cut_rod(std::vector<int> prices, int n){
    std::vector<int> r(n+1);
    r.at(0) = 0;

    for(int i = 1; i <= n; i++){
        int max = 0;
        for(int j = 1; j <= i; j++){
            int q = prices.at(j) + r.at(i - j);
            if(q > max){
                max = q;
            }
        }
        r.at(i) = max;
    }
    return r.at(n);
}

struct rod_sol{
    std::vector<int> r;
    std::vector<int> s;
};

rod_sol bottom_up_cut_rod_ext(std::vector<int> prices, int n){
    std::vector<int> r(n+1);
    std::vector<int> s(n+1);
    
    r.at(0) = 0;
    s.at(0) = 0;

    for(int i = 1; i <= n; i++){
        int max = 0;
        for(int j = 1; j<=i; j++){
            int q = prices.at(j) + r.at(i-j);
            if(max < q){
                max = q;
                s.at(i) = j; 
            }
        }
        r.at(i) = max;
    }

    rod_sol sol;
    sol.r = r;
    sol.s = s;
    return sol;
}

void print_cut_rod(std::vector<int> prices, int n){
    rod_sol sol = bottom_up_cut_rod_ext(prices,n);
    while(n > 0){
        std::cout << sol.s.at(n) << " ";
        n = n - sol.s.at(n);
    }
    std::cout << std::endl;
}


int cut_price(std::vector<int> pri, std::vector<int> cuts, int n){
    std::vector<int> r(n+1);
    r.at(0) = 0;
    for(int i = 1; i <= n; i++){
        int price = pri.at(i);
        for(int j = 1; j < i; j++){
            int gain = pri.at(j) + r.at(i - j) - cuts.at(j);
            if(gain > price){
                price = gain;
            }
        }
        r.at(i) = price;
    }
    return r.at(n);
}

int cut_rod_printing(std::vector<int> prices, int n, std::vector<int> memo, std::vector<int> sol){
    if(memo.at(n)>= 0){
        return memo.at(n);
    }

    int pr = 0;
    for(int i = 1; i <= n; i++){
        int q = prices.at(i) + cut_rod_printing(prices,n-i,memo,sol);
        if(q >= pr){
            pr = q;
            sol.at(n) = i;
        }
    }

    memo.at(n) = pr;
    return pr;
}

int cut_print(std::vector<int> prices, int n){
    std::vector<int> memo(n+1);
    std::vector<int> sol(n+1);
    for(int i = 0; i < n+1; i++){
        memo.at(i) = INT32_MIN;
    }

    int q = cut_rod_printing(prices,n,memo,sol);
    rod_sol a;
    a.r = memo;
    a.s = sol;
    return q;
}

int fibbonaci(int n){
    std::vector<int> fib(n);
    fib.at(0) = 1;
    fib.at(1) = 1;
    if(n < 2) return fib.at(n);
    for(int i = 2; i < n; i++){
        fib.at(i) = fib.at(i - 1) + fib.at(i - 2);
    }
    return fib.back();

}

int main(void){
    std::vector<int> prices = {0,1,5,8,9,10,17,17,20,24,30};

    std::cout << "top down  : "  <<  memoized_cut_rod(prices,5) << std::endl;
    std::cout << "bottom up : "  <<  bottom_up_cut_rod(prices,5) << std::endl;

    rod_sol solutions = bottom_up_cut_rod_ext(prices,10);

    std::cout << "vector r = { ";
    for(size_t i = 0; i < solutions.r.size(); i++){
        std::cout << solutions.r.at(i) << " ";
    }
    std::cout << "}" << std::endl;


    std::cout << "vector s = { ";
    for(size_t i = 0; i < solutions.s.size(); i++){
        std::cout << solutions.s.at(i) << " ";
    }
    std::cout << "}" << std::endl;

    std::cout << "print : ";
    print_cut_rod(prices,5);
    
    std::cout << fibbonaci(6) << std::endl;
    return 0;
}
