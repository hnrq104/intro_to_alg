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
    double a = (square_root(5,5) - 1)/2;
    double point = k*a - int(k*a);
    return int(m*point);
}

struct open_addressing{
    std::vector<int*> keys;

    open_addressing(int n){
        keys.resize(n);
        for(int i = 0; i < n; i++){
            keys.at(i) == nullptr;
        }
    }

    /*
    int h(int k, int probe){
        //do later
    }

    int hash_insert(int k){
        for(int i = 0; i < keys.size(); i++){
            int j = h(k,i);
            if(keys.at(j) == nullptr){
                keys.at(j) = new int(k);
                return j;
            }
        }

        throw std::overflow_error("hash overflow");
    }

    int* hash_search(int k){
        for(int i = 0; i < keys.size(); i++){
            int j = h(k,i);
            if(*keys.at(j) == k){
                return keys.at(j);
            }
            i++;
        }

        return nullptr;
    }

    */

};

struct obj{
    char del;
    int data;
};


struct open{
    obj *vetor;
    int size;

    open(int m){
        vetor = new obj[m];
        for(int i = 0; i < m; i++){
            obj ob;
            ob.del = 0;
            *(vetor + i) = ob; 
        }
    }

    int h(int k){
        return k; //something 
    }

    int linear_h(int k, int i){
        return (h(k) + i)%size;
    }

    int quadratic_h(int k , int i, int c1, int c2){
        return (h(k) + c1*i + c2*i*i)%size;
    }


    int dh1(int k){
        return k;
    }

    int dh2(int k){
        return 1 + k%(size - 1);
    }

    int d_hashing(int k, int i){
        return (dh1(k) + i*dh2(k))%size;
    }

    int hashinsert_linear(int k){
        for(int i = 0; i < size; i++){
            int pos = linear_h(k,i);
            obj* t = vetor + pos;
            if(!t->del){
                t->data = k;
                return pos;
            }
        }

        throw std::overflow_error("hash overflow");
    }

    int hashinsert_quadratic(int k,int c1, int c2){
        for(int i = 0; i < size; i++){
            int pos = quadratic_h(k,i,c1,c2);
            obj* t = vetor + pos;
            if(!t->del){
                t->data = k;
                return pos;
            }
        }

        throw std::overflow_error("hash overflow");
    }

    int hashinsert_double(int k){
        for(int i = 0; i < size; i++){
            int pos = d_hashing(k,i);
            obj* t = vetor + pos;
            if(!t->del){
                t->data = k;
                return pos;
            }
        }

        throw std::overflow_error("hash overflow");
    }



};




int main(void){
    std::cout << hash11(1000,61) << std::endl;
    std::cout << hash11(1000,62) << std::endl;
    std::cout << hash11(1000,63) << std::endl;
    std::cout << hash11(1000,64) << std::endl;
    std::cout << hash11(1000,65) << std::endl;
    
    // std::cout<< square_root(5,5)<<std::endl;
    return 0;
}