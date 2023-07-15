#include <bits/stdc++.h>

struct two
{
    int copies;
    int small;
};

void swap(std::vector<int> &v, int a, int b){
    int tmp = v.at(a);
    v.at(a) = v.at(b);
    v.at(b) = tmp;
}

two partition_(std::vector<int> &v , int start, int end){
    int pivot = v.at(end - 1);
    int q = start - 1;
    int t = start - 1;

    for(int j = start; j < end - 1; j++){
        if(v.at(j) == pivot){
            t++;
            swap(v,j,t);
        }

        if(v.at(j) < pivot){
            q++;
            t++;
            
            swap(v,q,j);
            swap(v,t,j);
        }
    }

    swap(v,end - 1, t + 1);
    two qt;
    qt.copies = q + 1; // first element that is a copy
    qt.small = t + 1; // last element less or equal

    return qt;

}

void quicksort_(std::vector<int> &v, int start, int end){
    if(start < end - 1){
        two t = partition_(v,start,end);
        quicksort_(v,start,t.copies);
        quicksort_(v,t.small + 1, end);
    }
}


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
    // std::random_device rd; // seeder
    // std::mt19937 gen(rd()); 
    // std::uniform_int_distribution<> distrib(0,0xfffffff);
    // std::vector<int> to_be_sorted;

    // for(int i = 0; i < 100000; i++){
    //     to_be_sorted.push_back(distrib(gen));
    // }

    // clock_t start,end;
    // start = clock();
    // quicksort(to_be_sorted,0,to_be_sorted.size());
    // end = clock();
    
    // double time_taken = double(end - start)/double(CLOCKS_PER_SEC);


    // std::cout << "sorted : " << is_Sorted(to_be_sorted) << std::endl;
    // std::cout /*<< std::hex */  << std::setprecision(5) << time_taken << "s";
    // std::cout << std::endl;

    std::vector<int> test_part = {5,3,1,2,3,1,2,4,1,2,3,4,5,3,2,4,3};
    // two answer = partition_(test_part,0,test_part.size());
    quicksort_(test_part,0,test_part.size());
    for(size_t i = 0; i < test_part.size(); i++){
        std::cout << test_part.at(i) << " ";
    }
    // std::cout << "\ntwo - " << answer.copies << " - " << answer.small << std::endl;

    return 0;
}

/*
https://math.mit.edu/~goemans/18310S15/rand_median_quicksort-notes.pdf
*/