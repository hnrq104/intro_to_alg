#include <bits/stdc++.h>

int euclid(int a, int b){
    if(b==0) return a;
    else return euclid(b,a%b);
}

std::vector<int> extended_euclid(int a, int b){
    if(b==0) return {a,1,0};
    
    auto v = extended_euclid(b,a%b);
    return {v[0],v[2], v[1] - (a/b)*v[2]};
}



/*iterative euclid*/
int iterative_euclid(int a, int b){ //these are copies, so they can be changed
    while(b != 0){
        int tmp = a;
        a = b;
        b = tmp%b;
    }
    return a;
}

int memoized_fib(uint n){
    static std::vector<int> f = {0,1};

    if(n < f.size()){
        return f.at(n);
    }

    for(uint i = f.size(); i <= n; i++){
        f.push_back(f.at(i-1) + f.at(i - 2));
    }

    return f.at(n);

}

int lcm(std::vector<int> numbers){
    int prod = 1;
    for(auto n : numbers){
        prod = (prod * n)/euclid(prod,n);
    }
    return prod;
}

std::vector<int> modular_linear_equation_solver(int a, int b, int n){
    auto d = extended_euclid(a,n);
    std::vector<int> solutions;
    if(b % d.at(0) == 0){
        int x0 = d.at(1)*(b/d.at(0)) % (n/d.at(0));
        for(int i = 0; i <= d.at(0) - 1; i++){
            solutions.push_back((x0 + i*(n/d.at(0))) % n);
        }
    }

    return solutions;
}

int modular_exponentiation_reversed(int a, int b, int n){
    int c = 1;
    while(c < b) c = c << 1;

    int d = 1;
    while(c>0){
        if(c&b){
            d = (d*a) % n;
        }
        d = (d*d) % n;
        c = c>>1;
    }

    return d;
}

int modular_exponentiation(int a, int b, int n){ 
    /*this was the one I made back in the first period*/
    /*i felt bad that I couldn't do it immediately without looking*/   
    /*the main idea is computing a^(2^k) and multiplying to get the number in binary*/
    int d = 1;
    int pot = a; //a^(2^k)

    while(b>0){
        if(b%2) d = (d*pot)%n;
        pot = (pot*pot)%n;
        b = b>>1;
    }
    return d;
}

bool pseudoprime(int n){
    if(modular_exponentiation(2,n-1,n) != 1) return true; //certainly composite
    return false; //we hope it's prime
}

bool witness(int a, int n){
    int u = n - 1;
    int t = 0;
    while(u % 2 == 0){
        t++;
        u = u >> 1;
    }

    int xprev = modular_exponentiation(a,u,n);
    for(int i = 0; i < t; i++){
        int x = (xprev*xprev)%n;

        if(x == 1 && (xprev != n-1 && xprev != 1)){
            return true;
        }
        xprev = x;
    }

    if(xprev != 1) return true;
    return false;
}

bool miller_rabin(int n, int s, std::mt19937 &twister){
    std::uniform_int_distribution<> d(2,n-1);
    for(int i = 0; i < s; i++){
        int a = d(twister);
        if(witness(a,n)){
            return true; /*composite*/
        }
    }
    return false; //prime
}

std::set<int> pollard_rho(int n,int s,std::mt19937 &twister){
    std::uniform_int_distribution<> d(0,n-1);
    int x = d(twister);

    int y = x;
    int k = 2;
    std::set<int> factors;
    for(int i = 0; i < s; i++){
        x = (x*x - 1)%n;
        if(x < 0) x = n - x;
        int d = euclid(abs(y-x),n);
        if(d != 1 && d != n && factors.find(d) == factors.end()) factors.emplace(d);
        if(i == k){
            y = x;
            k = 2*k;
        }
    }
    return factors;
}


int main(void){
    std::mt19937 gen(100);
    std::uniform_int_distribution<> distrib;

    std::unordered_map<uint,uint> gcd;
    for(uint i = 0; i < 1000; i++){
        auto a = distrib(gen);
        auto b = distrib(gen);

        uint c = euclid(a,b);
        auto itr = gcd.find(c);
        if(itr == gcd.end()){
            gcd.insert(std::make_pair(c,1));
        }
        else itr->second++;
    }

    int sum = 0;
    for(const auto& i : gcd){
        std::cout << "gcd : " << i.first << " counts: " << i.second << std::endl;
        sum+=i.second;
    }

    std::cout << sum << std::endl;


    auto v = extended_euclid(3,280);
    
    for(auto i : v){
        std::cout << i << " ";
    }

    std::cout<<std::endl;


    for(auto i : modular_linear_equation_solver(14,30,100)){
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "7^560 mod 561 = " << modular_exponentiation(7,560,561) << std::endl;

    /*exercise 31.7-1*/
    int p = 11;
    int q = 29;
    int n = (p-1)*(q-1) + v.at(1);
    std::cout << modular_exponentiation(100,3,p*q)<<std::endl;
    std::cout << modular_exponentiation(254,n,p*q)<<std::endl;

    std::cout << miller_rabin(12513,10,gen) << std::endl;

    /*pollard rho test*/
    std::cout << "pollard rho 1387 : ";
    for(auto i : pollard_rho(5*7*17*29*13,50,gen)){
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << euclid(814-84,1387) << std::endl;

    return 0;
}