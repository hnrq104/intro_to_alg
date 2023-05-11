#include <bits/stdc++.h>
//hash functions

//division method
//find prime close to load factor

size_t division_method(size_t k, int m){
    return k%m;
}

size_t multiplication_method(double A, int p, int k){
    int w = 32;
    size_t product =size_t(A*(1<<w));
    std::cout << product << std::endl;
    size_t last_32bits  = (k*product) % (1<<w);
    std::cout << last_32bits << std::endl;
    size_t p_bits = last_32bits>>w;
    p_bits = p_bits>>(w-p);

    return p_bits;
}

int main(void){
    std::cout << multiplication_method(0.618033,14, 123456) << std::endl;
    return 0;
}
