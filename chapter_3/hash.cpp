#include <bits/stdc++.h>
//hash functions

//division method
//find prime close to load factor

struct fruta{
    int chave;
    int coisa;
    struct fruta *ant;
    struct fruta *prox;
};



class hash{
    private:
        std::vector<struct fruta*> cups;
        size_t a;
        size_t b;

    public:
        hash(){
            for(size_t i = 0; i < 31; i++){
                cups.push_back(nullptr);
            }

            a = rand()%30 + 1;
            b = rand()%31;
        }

        size_t hashing(int k){
            return (a*k + b)%31;
        }

        void insert(fruta f){
            size_t pos = hashing(f.chave);

            if(cups.at(pos) == nullptr){
                f.ant = nullptr;
                f.prox = nullptr;
                cups.at(pos) = new fruta(f);
                return;
            }

            else{
                fruta *ptr = cups.at(pos);
                while(ptr->prox != nullptr){
                    ptr = ptr->prox;
                }
                f.ant = ptr;
                f.prox = nullptr;
                ptr->prox = new fruta(f);
            }
            
            return;
        }
};

double square_root(double x,int terms){
    double n = x;
    for(int i = 0; i < terms;i++){
        n = (n + x/n)/2;
    }
    return n;
}

int hash11(int m, int k){
    double a = square_root(5,5);
    double point = k*a - int(k*a);
    return int(m*point);
}

int main(void){
    std::cout << hash11(1000,61) << std::endl;
    std::cout << hash11(1000,62) << std::endl;
    std::cout << hash11(1000,63) << std::endl;
    std::cout << hash11(1000,64) << std::endl;
    std::cout << hash11(1000,65) << std::endl;

    // std::cout<< square_root(5,5)<<std::endl;
    return 0;
}