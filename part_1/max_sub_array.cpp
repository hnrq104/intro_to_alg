#include <iostream>
#include <random>
#include <vector>
#include <bits/stdc++.h>

/*for a possible version which shows the positions*/

class max_sub_array{
    public:
        size_t in_pos;
        size_t end_pos;
        int sum;

        max_sub_array(){
        };

        max_sub_array(size_t start, size_t end, int s){
            in_pos = start;
            end_pos = end;
            sum = s;
        }

        max_sub_array(max_sub_array &copy){
            in_pos = copy.in_pos;
            end_pos = copy.end_pos;
            sum = copy.sum;
        }
};

max_sub_array find_crossing(std::vector<int> &v, size_t start, size_t middle, size_t end){
    int left_sum = INT_MIN;
    int sum = 0;

    size_t index_s;
    for(int i = middle; i >= (int) start; i--){
        sum += v.at(i);
        if(sum > left_sum){
            left_sum = sum;
            index_s = i;
        }
    }


    sum = 0;
    int right_sum = INT_MIN;
    size_t index_end;
    for(size_t i = middle+1; i <= end; i++){
        sum += v.at(i);
        if(sum > right_sum){
            right_sum = sum;
            index_end = i;
        }
    }

    return max_sub_array(index_s, index_end, left_sum + right_sum);

}

max_sub_array find_max_value(std::vector<int> &v, size_t start, size_t end){
    

    if(start != end){
        size_t middle = (start + end)/2;
        max_sub_array left = find_max_value(v,start,middle); //divide
        max_sub_array right = find_max_value(v,middle+1,end); //divide

        max_sub_array crossing = find_crossing(v,start,middle,end); //conquer

        if(left.sum > right.sum && left.sum > crossing.sum){
            return left;
        }
        else if(right.sum > left.sum && right.sum > crossing.sum){
            return right;
        }
        else{
            return crossing;
        }
    }

    return max_sub_array(start,end,v.at(start));

}

max_sub_array find_max(std::vector<int> &v){
    max_sub_array answer = find_max_value(v,0,v.size() - 1);
    answer.end_pos++;

    return answer;
}


max_sub_array linear_find(std::vector<int> &v){

    max_sub_array max(0,1,v.at(0)) ;
    //knowing a maximum subarray of a[1,j-1]

    max_sub_array end(0,1,v.at(0));
    //knowing a maximum subarray that ends at j-1;

    /* a maximum subarray of a[1,j] is either a maximum subarray of a[1,j-1]
    * or is the maximum subarray ending at j-1 + a[j];
    */

   
   for(size_t j = 1; j < v.size(); j++){
        //calculates new end :if last one was negative throw it out, else sum
        if(end.sum < 0){
            end.in_pos = j;
            end.end_pos = j+1;
            end.sum = v.at(j);
        }
        else{
            end.end_pos = j+1;
            end.sum += v.at(j);
        }

        //compare to max;
        if(end.sum > max.sum){
            max = end;
        }

   }

    return max;
}



int main(void){
    std::vector<int> stock_change{4,-2,5,-1,-3};
    max_sub_array answer = find_max_value(stock_change,0,stock_change.size()-1);
    std::cout << "The biggest sum sub_array is:" << std::endl;
    for(size_t i = answer.in_pos; i < answer.end_pos; i++){
        std::cout << stock_change.at(i) << " ";
    }
    std::cout << std::endl;
    std::cout << "the sum is " << answer.sum << std::endl;

    std::cout << std::endl;

    // the same for linear finding
    max_sub_array linear_answer = linear_find(stock_change);
    std::cout << "LINEAR FINDING : " << std::endl;
    for(size_t i = linear_answer.in_pos; i < linear_answer.end_pos; i++){
        std::cout << stock_change.at(i) << " ";
    }
    std::cout << std::endl;
    std::cout << "the sum is : " << linear_answer.sum << std::endl;
    
    return 0;
}
