#include <bits/stdc++.h>


inline size_t left(size_t index){
    return (index << 1) + 1; 
}
inline size_t right(size_t index){
    return ((index + 1) << 1);
}
//notice that we now count from 1;
void max_heapify(std::vector<int> &v, size_t i){
    size_t l  = left(i);
    size_t r = right(i);
    size_t largest = i;

    if(l < v.size() && v.at(l) > v.at(largest)){
        largest = l;
    }
    if(r<v.size() && v.at(r) > v.at(largest)){
        largest = r;
    }

    if(largest != i){
        int tmp = v.at(largest);
        v.at(largest) = v.at(i);
        v.at(i) = tmp;

        max_heapify(v,largest);
    }
}

void iter_max_heapify(std::vector <int> &v, size_t i){
    size_t father = i;
    size_t largest = father;
    size_t l = left(father);
    size_t r = right(father);

    while(l < v.size() || r < v.size()){
        if(l < v.size() && v.at(l) > v.at(largest)){
            largest = l;
        }
        if(r<v.size() && v.at(r) > v.at(largest)){
            largest = r;
        }

        if(largest == father){ // it is in accordance to max_heap
            break;
        }

        int tmp = v.at(largest); //swap
        v.at(largest) = v.at(father);
        v.at(father) = tmp;

        father = largest; // father becomes root of new subtree
        l = left(father); // update values of l and r
        r = right(father);
    
    }
}