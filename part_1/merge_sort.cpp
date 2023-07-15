#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <random>


void merge(std::vector<int> &v, size_t start, size_t middle, size_t end){
    size_t max = end - start; // size of the sorted section
    int temporary_array[max];

    size_t i = start; // index of first half
    size_t j = middle; // index of second half
    
    size_t k = 0; // index of temporary array

    while(i < middle && j < end){
        if(v.at(i) < v.at(j)){
            temporary_array[k] = v.at(i);
            i++;
        }

        else{
            temporary_array[k] = v.at(j);
            j++;
        }

        k++;
    }

    //now we have to complete

    if(i != middle){ // i has not finished
        while(k != max){
            temporary_array[k] = v.at(i);
            i++;
            k++;
        }
    }

    if(j != end){ // j has not achieved end;
        while(k != max){
            temporary_array[k] = v.at(j);
            k++;
            j++;
        }
    }

    //then gotta copy all back
    for(k = 0; k < max; k++){
        v.at(start + k) = temporary_array[k];
    }

}


/***
 * start = position of first
 * end = position of last + 1
*/
void merge_sort(std::vector<int> &v, size_t start, size_t end){
    if(end - start > 1){
        size_t middle = (start + end)/2;
        merge_sort(v,start,middle);
        merge_sort(v,middle,end);
        merge(v,start,middle,end);
    }
}


int search_sorted(std::vector<int> &v, int n){
    // interactive version
    size_t start = 0;
    size_t end = v.size();
    size_t middle;

    while(end - start > 1){
        middle = (start + end)/2;
        
        if(n == v.at(middle)){
            return 1;
        }

        if(n > v.at(middle)){
            start = middle;
        }

        else{
            end = middle;
        }
    }

    return 0;
}

int two_to_sum(std::vector<int> copy, int number){
    //knowing that is already a copy
    merge_sort(copy,0,copy.size());

    size_t i = 0; // index on start
    size_t j = copy.size() - 1; // index on end

    int sum;
    while(i != j){
        sum = copy.at(i) + copy.at(j);
        if(sum == number) return 1;

        if(sum < number) i++;
        else j--;
    }

    return 0;
    //the idea is start summing the extremes
    //if the value is bigger than what we want, we diminish end
    //if it's smaller we increase start 
}



int combine_inversion(std::vector<int> &v, size_t start, size_t middle, size_t end){
    size_t max = end - start; // size of the sorted section
    int temporary_array[max];

    size_t i = start; // index of first half
    size_t j = middle; // index of second half
    
    size_t k = 0; // index of temporary array

    size_t inversions = 0; // counting the new inversions

    while(i < middle && j < end){
        if(v.at(i) <= v.at(j)){ // it has to be less or equal, equality does not count as inversion
            temporary_array[k] = v.at(i);
            i++;
        }

        else{
            temporary_array[k] = v.at(j);
            inversions += middle - i;
            j++;
        }

        k++;
    }

    //now we have to complete

    if(i != middle){ // i has not finished
        while(k != max){
            temporary_array[k] = v.at(i);
            i++;
            k++;
        }
    }

    if(j != end){ // j has not achieved end;
        while(k != max){
            temporary_array[k] = v.at(j);
            k++;
            j++;
        }
    }

    //then gotta copy all back
    for(k = 0; k < max; k++){
        v.at(start + k) = temporary_array[k];
    }

    return inversions;


}


int count_inversions_sub(std::vector<int> &v, size_t start, size_t end){
    if(end - start > 1){ 
        size_t middle = (start + end)/2;
        size_t inversions = 0;

        inversions += count_inversions_sub(v,start,middle); //inversions on the left side
        inversions += count_inversions_sub(v,middle,end); // inversions on the right side

        inversions += combine_inversion(v,start,middle,end); // inversions by putting both together

        return inversions;
    }

    // if there's only one number, there can't be inversions
    return 0;
}

//the one to actually use to avoid getting it sorted;
int count_inversion(std::vector <int> v){
    return count_inversions_sub(v,0,v.size());
}


int main(void){
    std::vector<int> to_sort{2,3,8,6,1};
    
    std::cout << "count inversions : ";
    std::cout << count_inversion(to_sort) << std::endl;


    merge_sort(to_sort,0,to_sort.size());
    std::cout << "sorted array : ";
    for(size_t i = 0; i < to_sort.size(); i++){
        std::cout << to_sort.at(i) << " ";
    }
    std::cout << std::endl;

    std::cout << "binary search : ";
    std::cout << search_sorted(to_sort,40) << std::endl;

    std::cout << "two_to_sum : ";
    std::cout << two_to_sum(to_sort,64) << std::endl;


    return 0;
}