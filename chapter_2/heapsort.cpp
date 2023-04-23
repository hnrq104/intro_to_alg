#include <bits/stdc++.h>
#include <random>
//ta mal feito

class heap{
    public:
        std::vector<int> *list;
        size_t heap_size;

        void max_heapify(size_t i);
        void build_max_heap(void);

        heap(std::vector<int> &copy){
            list = &copy;
            heap_size = list->size();
            build_max_heap();
        }

        int &at(size_t index){
            return list->at(index);
        }

        size_t size(void){ //so pra n reescrever tudo
            return heap_size;
        }

};
/*adicionado depois, faria de outra forma*/


inline size_t left(size_t index){
    return (index << 1) + 1; 
}
inline size_t right(size_t index){
    return ((index + 1) << 1);
}
//notice that we now count from 1;



//should be in class
void heap::max_heapify(size_t i){
    size_t l  = left(i);
    size_t r = right(i);
    size_t largest = i;

    if(l < size() && at(l) > at(largest)){
        largest = l;
    }
    if(r < size() && at(r) > at(largest)){
        largest = r;
    }

    if(largest != i){
        int tmp = at(largest);
        at(largest) = at(i);
        at(i) = tmp;

        max_heapify(largest);
    }
}

void iter_max_heapify(heap &v, size_t i){
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

void heap::build_max_heap(void){
    for(int i = list->size()/2 ; i >= 0; i--){
        max_heapify(i);
    }
}


void heapsort(std::vector<int> &v){
    //build max_heap
    heap h = v; //can i do this?

    //losing time copying ;; fixed using pointers still shit
    for(int i = v.size() - 1; i>= 1; i--){
        int tmp = h.at(0);
        h.at(0) = h.at(i);
        h.at(i) = tmp;
        h.heap_size--;
        
        h.max_heapify(0);
    }
}

bool is_Sorted(std::vector<int> &v){
    for(size_t i = 1; i < v.size(); i++){
        if(v.at(i - 1) > v.at(i)) return false;
    }
    return true;
}

/* priority queue   */

int main(void){
    std::random_device rd; // seeder
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distrib(0,0xfffffff);
    std::vector<int> to_be_sorted;

    for(int i = 0; i < 100000; i++){
        to_be_sorted.push_back(distrib(gen));
    }

    clock_t start,end;
    start = clock();
    heapsort(to_be_sorted);
    end = clock();
    
    double time_taken = double(end - start)/double(CLOCKS_PER_SEC);


    std::cout << "sorted : " << is_Sorted(to_be_sorted) << std::endl;
    std::cout /*<< std::hex */  << std::setprecision(5) << time_taken << "s";
    std::cout << std::endl;


    return 0;
}