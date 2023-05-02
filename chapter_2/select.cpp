#include <bits/stdc++.h>

void insertion_sort(std::vector<int> &v, int start, int end){
    for(int j = start + 1; j < end; j++){
        int key = v.at(j);
        int i = j - 1;
        while(i >= start && v.at(i) > key){
            v.at(i + 1) = v.at(i);
            i--;
        }
        v.at(i+1) = key;
    }
}


int partition(std::vector<int> &v, int start, int end, int input){
    int p = v.at(input); //will partition around element input
    v.at(input) = v.at(start);
    v.at(start) = p;

    int i = start + 1;
    for(int j = start + 1; j < end; j++){
        if(v.at(j) <= p){
            int tmp = v.at(j);
            v.at(j) = v.at(i);
            v.at(i) = tmp;
            i++;
        }
    }

    v.at(start) = v.at(i-1);
    v.at(i - 1) = p;

    return i - 1;
}

int select(std::vector<int> &v, int start, int end, int index){
    if(start + 1 == end){
        return v.at(start);
    }

    int n_elements = (end - start); //elements
    int n_groups_5 = n_elements/5; //n of groups with 5 elements
    int size_of_last = n_elements%5; // size of last group

    //insertion sort each of the 5 groups
    for(int i = 0; i < n_groups_5; i++){
        insertion_sort(v,5*i, 5*(i+1));
    }
    //insertion sort last group
    insertion_sort(v,5*n_groups_5,end);
    
    std::vector<int> medians;
    for(int i = 0; i < n_groups_5; i++){
        medians.push_back(v.at(5*i + 2)); // third element of each group
    }

    //median of last group stands at (size_of_last - 1)/2
<<<<<<< HEAD
    if(size_of_last){
        medians.push_back(v.at(5*n_groups_5 + (size_of_last-1)/2));
    }
=======
    medians.push_back(v.at(5*n_groups_5 + (size_of_last-1)/2));
>>>>>>> refs/remotes/origin/main
    
    int m = select(medians,0,medians.size(),(medians.size()-1)/2);
    
    //can be better, but doesn't change time, because it's O(n)
    int p;
    for(int i = 0; i < n_groups_5; i++){
        if(v.at(5*i + 2) == m){
            p = 5*i + 2;
            break;
        }
    }

<<<<<<< HEAD
    if(size_of_last){
        if(v.at(5*n_groups_5 + (size_of_last-1)/2) == m){
            p = 5*n_groups_5 + (size_of_last-1)/2;
        }
=======
    if(v.at(5*n_groups_5 + (size_of_last-1)/2) == m){
        p = 5*n_groups_5 + (size_of_last-1)/2;
>>>>>>> refs/remotes/origin/main
    }

    //found position of given median
    int k = partition(v,start,end,p);
    if(k == index){
        return v.at(k);
    }
    if(index < k){
        return select(v,start,k,index);
    }
    else{
        return select(v,k+1,end,index);
    }

}


<<<<<<< HEAD
int main(void){
    
    std::vector<int> v{1,3,0,5,2,3,6,1,2,12,125,16,20};

    //its alive

    std::cout << select(v,0,v.size(),1) << std::endl;
=======


int main(void){
    std::vector<int> v{0,5,4,2,1,6,7,10,8,9,3};
    //its alive
    std::cout << select(v,0,v.size(),10) << std::endl;
>>>>>>> refs/remotes/origin/main

    return 0;
}