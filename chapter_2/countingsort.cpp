#include <bits/stdc++.h>


//counting works from 0 - n
// it is easy to make it work from min - max
size_t find_max(std::vector<size_t> &v){
    size_t max  = 0;
    for(size_t i = 0; i < v.size(); i++){
        if(v.at(i) > max){
            max = v.at(i);
        }
    }
    return max;
}

void countingsort(std::vector<size_t> &v){
    std::vector<size_t> c(find_max(v) + 1);
    std::vector<size_t> b(v.size());

    for(size_t i = 0; i < c.size(); i++){
        c.at(i) = 0;
    }

    for(size_t i = 0; i < v.size(); i++){
        c.at(v.at(i))++;
    }

    for(size_t i = 1; i < c.size(); i++){
        c.at(i) += c.at(i-1);
    }


   for(int i = v.size() - 1; i >= 0; i--){
        b.at(c.at(v.at(i)) - 1) = v.at(i);
        c.at(v.at(i))--;
    }   

    v = b;
}

template<typename T>
bool isSorted(std::vector<T> &comparable){
    for(size_t i = 1; i < comparable.size(); i++){
        if(comparable.at(i) < comparable.at(i-1)){
            return false;
        }
    }

    return true;
}

int main(void){

    std::vector<size_t> v{0,5,2,3,5,1,6,7,9,12};
    countingsort(v);
    for(size_t i = 0; i < v.size(); i++){
        std::cout << v.at(i) << " ";
    }
    std::cout << std::endl;
    return 0;
}