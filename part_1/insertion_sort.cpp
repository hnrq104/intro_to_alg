#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <random>


void insertion_sort_inc(std::vector<int> &v){
    for(size_t i = 1; i < v.size(); i++){
        int tmp = v.at(i);
        
        int j = i - 1;
        
        while(j >= 0 && v.at(j) > tmp){
            v.at(j+1) = v.at(j);
            j--;
        }

        v.at(j+1) = tmp;
    }

    return;
}

void insertion_sort_dec(std::vector<int> &v){
    for(size_t i = 1 ; i < v.size(); i++){
        int tmp = v.at(i);

        int j = i - 1;
        while(j>= 0 && v.at(j) < tmp){
            v.at(j+1) = v.at(j);
            j--;
        }

        v.at(j+1) = tmp;
    }
}

void recurrent_insertion_sort(std::vector<int> &v, size_t end){
    if(end != 0){
        recurrent_insertion_sort(v,end - 1);
        
        int tmp = v.at(end-1);
        int j = end - 2;

        while(j >= 0 && v.at(j) > tmp){
            v.at(j+1) = v.at(j);
            j--;
        }

        v.at(j+1) = tmp;
    }

}

int main(void){
    std::random_device rd; // seeder
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distrib(0,50);
    std::vector<int> to_be_sorted;

    for(int i = 0; i < 10; i++){
        to_be_sorted.push_back(distrib(gen));
    }

    insertion_sort_inc(to_be_sorted);
    std::cout <<  "INSERTION-SORT INCREASING : \n";
    for(size_t i = 0; i < to_be_sorted.size(); i++){
        std::cout << to_be_sorted.at(i) << " ";
    }
    std::cout << "\n";


    insertion_sort_dec(to_be_sorted);
    std::cout <<  "INSERTION-SORT DECREASING : \n";
    for(size_t i = 0; i < to_be_sorted.size(); i++){
        std::cout << to_be_sorted.at(i) << " ";
    }
    std::cout << "\n";


    recurrent_insertion_sort(to_be_sorted,to_be_sorted.size());
    std::cout <<  "RECURSIVE INSERTION-SORT INCRESING : \n";
    for(size_t i = 0; i < to_be_sorted.size(); i++){
        std::cout << to_be_sorted.at(i) << " ";
    }
    std::cout << "\n";


    return 0;
}