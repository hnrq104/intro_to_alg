#include <bits/stdc++.h>



int partition(std::vector<int> &v, int start, int end){
    int p = v.at(start);

    int i = start + 1;
    for(int j = start + 1; j < end; j++){
        if(v.at(j) <= p){
            int tmp = v.at(j);
            v.at(j) = v.at(i);
            v.at(i) = tmp;
            i++;
        }
    }
    int tmp = v.at(i - 1);
    v.at(i - 1) = v.at(start);
    v.at(start) = tmp; 
    
    return i - 1;
}

void quicksort(std::vector<int> &v, int start, int end){
    if(start < end - 1){
        int q = partition(v,start,end);
        quicksort(v,start,q);
        quicksort(v,q + 1,end);
    }
}

bool is_Sorted(std::vector<int> &v){
    for(size_t i = 1; i < v.size(); i++){
        if(v.at(i - 1) > v.at(i)) return false;
    }
    return true;
}

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
    quicksort(to_be_sorted,0,to_be_sorted.size());
    end = clock();
    
    double time_taken = double(end - start)/double(CLOCKS_PER_SEC);


    std::cout << "sorted : " << is_Sorted(to_be_sorted) << std::endl;
    std::cout /*<< std::hex */  << std::setprecision(5) << time_taken << "s";
    std::cout << std::endl;

    return 0;
}