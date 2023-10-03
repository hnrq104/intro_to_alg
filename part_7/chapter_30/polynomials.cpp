#include <bits/stdc++.h>
#include <bit>
using namespace std;
complex<double> horners(vector<complex<double>> &coefficients, complex<double> &x){
    complex<double> value = coefficients.back();
    for(int i = coefficients.size()-2; i>=0; i--){
        value *= x;
        value += coefficients.at(i);
    }
    return value;
}

vector<complex<double>> add(vector<complex<double>> &lhs, vector<complex<double>> &rhs){
    vector<complex<double>> result(max(lhs.size(),rhs.size()),0);
    uint tam = result.size();
    for(uint i = 0; i < tam; i++){
        if(i < lhs.size()){
            result.at(i)+=lhs.at(i);
        }
        if(i < rhs.size()){
            result.at(i)+=rhs.at(i);
        }
    }

    return result;
    /*this is not the most optimal way, but it is the simplest*/
}

vector<complex<double>> standard_convolution(vector<complex<double>> &lhs, vector<complex<double>> &rhs){
    vector<complex<double>> result(lhs.size() + rhs.size(),0);
    uint tam = result.size();

    for(uint i = 0; i < tam; i++){
        complex<double> sum = 0;
        for(uint j = 0; j <= i; j++){
            sum+= lhs.at(j)*rhs.at(i-j);
        }
        result.at(i) = sum;
    }

    return result;
}

/*exercise 30.1-2,
Another way to evaluate a polynomial A(x) of degree-bound n at a given point x0
is to divide A(x) by the polinomial (x-x0), obtaining a quotient polynomial q(x) of
degree bound n-1 and a remainder r, such that
A(x) = q(x) * (x - x0) + r 
Clearly A(x0) = r. Show how to compute the remainder r and teh coefficients of q(x) in time O(n)
from x0 and the coefficients of A */

/*coefficients and remainder*/
vector<complex<double>> division(vector<complex<double>> &lhs, complex<double> x0){
    vector<complex<double>> result(lhs.size()); /*number at pos 0 is remainder*/
    result.back() = lhs.back();
    for(int i = result.size()-2; i >= 0; i--){
        result.at(i) = lhs.at(i) + result.at(i+1)*x0;
    }
    return result;
}

/*recursive fft, I will suppose the vector given has size 2^n*/
vector<complex<double>> recursive_fft(vector<complex<double>> &a){
    uint n = a.size();
    if(n == 1){
        return {a.at(0)}; // a avaliated at w01 = 1
    }

    complex<double> wn = {cos(2*M_PI/n), sin(2*M_PI/n)}; //principal nth root of unity
    complex<double> w = 1; 

    vector<complex<double>> a0(n/2,0); //coefficients of even powers
    vector<complex<double>> a1(n/2,0); //coefficients of odd powers
    for(uint i = 0; i < n/2; i++){
        a0.at(i) = a.at(2*i);
        a1.at(i) = a.at(2*i + 1); 
    }

    auto y0 = recursive_fft(a0);
    auto y1 = recursive_fft(a1);

    vector<complex<double>> y(n);
    //A(x) = A[0](x^2) + x*A[1](x^2)
    for(uint k = 0; k < n/2; k++){
        //yk = y0_k + w^{k}_n * y1_k for every k
        auto tmp = w*y1.at(k); //complex tmp
        y.at(k) = y0.at(k) + tmp;
        y.at(k + n/2) = y0.at(k) - tmp;
        w = w*wn;
    }

    return y;
}


/*recursive fft, I will suppose the vector given has size 2^n*/
vector<complex<double>> recursive_inverse_dft(vector<complex<double>> &a){
    uint n = a.size();
    if(n == 1){
        return {a.at(0)}; // a avaliated at w01 = 1
    }

    complex<double> wn = {cos(2*M_PI/n), sin(2*M_PI/n)}; //principal nth root of unity
    wn = 1./wn;// need wn^-1
    complex<double> w = 1; 

    vector<complex<double>> a0(n/2,0); //coefficients of even powers
    vector<complex<double>> a1(n/2,0); //coefficients of odd powers
    for(uint i = 0; i < n/2; i++){
        a0.at(i) = a.at(2*i);
        a1.at(i) = a.at(2*i + 1); 
    }

    auto y0 = recursive_fft(a0);
    auto y1 = recursive_fft(a1);

    vector<complex<double>> y(n);
    double len = n;//divide by n
    //A(x) = A[0](x^2) + x*A[1](x^2)
    for(uint k = 0; k < n/2; k++){
        //yk = y0_k + w^{k}_n * y1_k for every k
        auto tmp = w*y1.at(k); //complex tmp
        y.at(k) = (y0.at(k) + tmp)/len;
        y.at(k + n/2) = (y0.at(k) - tmp)/len;
        w = w*wn;
    }

    return y;
}

// vector<complex<double>> iterative_fft(vector<complex<double>> &a){
//     //bit reverse copy a,A
//     vector<complex<double>> A;
//     uint n = a.size();
//     for(uint m = 1; m < n; m*=2){
        
//     // complex<double> wn = {cos(2*M_PI/n), sin(2*M_PI/n)}; 
//         for(uint k = 0; k < n; k+=m){
//             complex<double> w = 1;

//             for(uint j = 0; j < m/2; j++){
//                 auto t = w*A.at(k + j + m/2);
//                 auto u = A.at(k+j);

//                 A.at(k+j) = u - t;
//                 A.at(k+j+ m/2)


//             }
//         }

//     }

// }




int main(void){
    vector<complex<double>> divided = {{3,0},{-4,0},{1,0}};
    
    auto result = division(divided,{2,0});
    for(auto i : result){
        cout << i << " ";
    }
    cout << endl;

    /*exercise 30.2-2*/
    vector<complex<double>> t = {{0,0},{1,0},{2,0},{3,0}};
    auto dft = recursive_fft(t);
    for(auto i : dft){
        cout << i << " ";
    }
    cout << endl;

    /*test inverse */
    auto inverse = recursive_inverse_dft(dft);
    for(auto i : inverse){
        cout << i << " ";
    }
    cout << endl;

    vector<complex<double>> A = {{1,0},{2,0},{3,0},{4,0}};
    vector<complex<double>> B = {{0,0},{2,0},{4,0},{8,0}};

    auto dfa = recursive_fft(A);
    auto dfb = recursive_fft(B);

    vector<complex<double>> product(A.size());
    for(uint i = 0; i < A.size(); i++){
        product.at(i) = A.at(i)*B.at(i);
    }

    auto reverse = recursive_inverse_dft(product);
    for(auto i : reverse){
        cout << i << " ";
    }
    cout << endl;

    return 0;
}