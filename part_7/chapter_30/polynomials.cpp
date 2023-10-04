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

/*recursive dft, I will suppose the vector given has size 2^n*/
vector<complex<double>> recursive_dft(vector<complex<double>> &a){
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

    auto y0 = recursive_dft(a0);
    auto y1 = recursive_dft(a1);

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


vector<complex<double>> recursive_inverse_dft_aux(vector<complex<double>> &a){
    uint n = a.size();
    if(n == 1){
        return {a.at(0)}; // a avaliated at w01 = 1
    }

    complex<double> wn = {cos(2*M_PI/n), sin(2*M_PI/n)}; //principal nth root of unity
    wn = 1./wn;
    complex<double> w = 1; 

    vector<complex<double>> a0(n/2,0); //coefficients of even powers
    vector<complex<double>> a1(n/2,0); //coefficients of odd powers
    for(uint i = 0; i < n/2; i++){
        a0.at(i) = a.at(2*i);
        a1.at(i) = a.at(2*i + 1); 
    }

    auto y0 = recursive_inverse_dft_aux(a0);
    auto y1 = recursive_inverse_dft_aux(a1);

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

/*recursive dft, I will suppose the vector given has size 2^n*/
vector<complex<double>> recursive_inverse_dft(vector<complex<double>> &a){
    auto y = recursive_inverse_dft_aux(a);
    double n = a.size();
    for(auto &i : y){
        i/=n;
    }
    return y;
}

uint bit_reversal(uint a,uint size){
    uint rev = 0;
    while(size > 1){ /*we're seing a power of two, so the last one shouldn't count*/
        rev = rev << 1;
        if(a&1){
            rev = rev^1; /*this xor will add the last bit as one*/
        }
        a = a >> 1;
        size = size >> 1;
    }
    
    return rev;
}

vector<complex<double>> iterative_dft(vector<complex<double>> &a){
    //bit reverse copy a,A
    vector<complex<double>> A(a.size());
    uint n = a.size();

    /*bit reverse A from a*/
    for(uint i = 0; i < n; i++){
        A.at(bit_reversal(i,n)) = a.at(i);
    }
    
    for(uint m = 1; m <= n; m*=2){
        complex<double> wn = {cos(2*M_PI/m), sin(2*M_PI/m)};  /*i think there's a smarter way*/
        
        complex<double> w = 1; /*this change came with 30.3-3 it is really better*/
        //i had thought of some optimization, glady it came as a question
        for(uint j = 0; j < m/2; j++){
 
            for(uint k = 0; k < n; k+=m){
                auto t = w*A.at(k + j + m/2);
                auto u = A.at(k+j);

                A.at(k+j) = u + t;
                A.at(k+j+ m/2) = u - t;
            }
            
            w *= wn;
        }
    }

    return A;
}


vector<complex<double>> iterative_inverse_dft(vector<complex<double>> &a){
    uint n = a.size();
    vector<complex<double>> A(n);
    //bit reverse copy a,A
    for(uint i = 0; i < n; i++){
        A.at(bit_reversal(i,n)) = a.at(i);
    }
    
    for(uint m = 1; m <= n; m*=2){
        complex<double> wn = complex<double>({cos(2*M_PI/m), sin(2*M_PI/m)});  /*i think there's a smarter way*/
        wn = 1./wn;

        complex<double> w = 1;
        for(uint j = 0; j < m/2; j++){
        
            for(uint k = 0; k < n; k+=m){
                auto t = w*A.at(k + j + m/2);
                auto u = A.at(k+j);

                A.at(k+j) = (u + t);
                A.at(k+j+ m/2) = (u - t);
            }
            
            w *= wn;
        }
    }

    /*bit reverse A*/
    double tam = n;
    for(auto &i : A){
        i /= tam;
    }

    return A;
}

/*I really don't know if I should, nor that I have the mental capacity
to do this right now, but i will try

Update:: i had, it worked lol
30.3-2*/

/*upside down inverse dft, should yield a normal dft with reverse bits at bottom*/
vector<complex<double>> dft_upside_down(vector<complex<double>> &a){ 
    uint n = a.size();
    vector<complex<double>> A(n);
    //bit reverse copy a,A
    
    double tam = n;
    for(auto &i : A){
        i *= tam;
    }
        
    for(uint m = n; m > 0; m/=2){
        complex<double> wn = complex<double>({cos(2*M_PI/m), sin(2*M_PI/m)});  /*i think there's a smarter way*/
        wn = 1./wn;

        for(uint k = 0; k < n; k+=m){
            complex<double> w = 1;
            for(uint j = 0; j < m/2; j++){
                // auto t = w*A.at(k + j + m/2);
                // auto u = A.at(k+j);

                // A.at(k+j) = (u + t);
                // A.at(k+j+ m/2) = (u - t);
                auto u = (A.at(k + j) + A.at(k + j + m/2))/2.0; //u
                auto t = (A.at(k + j) - A.at(k + j + m/2))/(2.*w); //t
                A.at(k+j) = u;
                A.at(k+j+m/2) = t;

                w *= wn;
            }
        }
    }

    /*bit reverse A*/
    for(uint i = 0; i < n; i++){
        A.at(bit_reversal(i,n)) = a.at(i);
    }

    return A;
}



int main(void){

    /*exercise 30.2-2*/
    cout << "recursive dft: "; 
    vector<complex<double>> t = {{1,0},{2,0},{3,0},{4,0}};
    auto dft = recursive_dft(t);
    for(auto i : dft){
        cout << i << " ";
    }
    cout << endl;

    /*text iterative*/
    cout << "iterative dft: "; 
    auto iterative = iterative_dft(t);
    for(auto i : iterative){
        cout << i << " ";
    }
    cout << endl;

    cout << "recursive inverse dft: "; 
    auto reverse = recursive_inverse_dft(dft);
    for(auto i : reverse){
        cout << i << " ";
    }
    cout << endl;


    cout << "iterative inverse dft: "; 
    auto reverse_it = iterative_inverse_dft(iterative);
    for(auto i : reverse_it){
        cout << i << " ";
    }
    cout << endl;


    cout << "true inverse inverse dft: "; /*FUNCIONOU KKKKKKKKKKKS*/
    auto up = dft_upside_down(iterative);
    for(auto i : up){
        cout << i << " ";
    }
    cout << endl;

    //exercise 30.3.1
    vector<complex<double>> e = {{0,0},{2,0},{3,0},{-1,0},{4,0},{5,0},{7,0},{9,0}};    
    auto it = iterative_dft(e);
    for(auto i : it){
        cout << i << " ";
    }
    cout << endl;
    
    
    return 0;
}