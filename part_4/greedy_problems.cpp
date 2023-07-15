#include <bits/stdc++.h>
#include <set>
#include <vector>

using namespace std;

/*16.1*/
int best_coins(int n,vector<int> coin_set, vector<int> &sol){
    vector<int> min_coin(n+1);
    min_coin.at(0) = 0;

    for(uint i = 0; i < n+1; i++){
        int min = n+1; // worst case only pennies but it doesnt matter, it will change
        for(uint j = 0; j < coin_set.size(); j++){
            if(coin_set.at(j) > i) break;
            if(min_coin.at(i - coin_set.at(j)) + 1 < min){
                min = min_coin.at(i - coin_set.at(j)) + 1;
                sol.at(i) = coin_set.at(j);
            }
        }
        min_coin.at(i) = min;
    }

    return min_coin.at(n);
}

struct task{
    int id;
    int pi;
};

bool comp_task(task a, task b){
    return a.pi < b.pi;
}
/*16.2*/
double schedule(vector<task> v){
    sort(v.begin(),v.end(),comp_task);
    // vector<int> completion;
    // completion.push_back(0);
    int sum = 0;
    int avarage_sum = 0;
    for(uint i = 0; i < v.size(); i++){
        sum += v.at(i).pi;
        avarage_sum += sum;
    }
    return avarage_sum/v.size();
}


//logkn^2 really bad 
vector<int> off_cache(vector<int> requests,uint k){
    vector<int> decisions;
    set<int> cache;
    uint occupied = 0;
    //many ways to make this better
    
    for(uint i = 0; i < requests.size(); i++){
        //cache hit
        if(cache.count(requests.at(i))) continue;

        //there's space in cache
        if(occupied < k){
            cache.insert(requests.at(i));
            occupied++;
            continue;
        }

        //find furthest
        uint distance = 0;
        uint furthest = 0;

        for(uint j = i + 1; j < requests.size(); j++){
            if(cache.count(requests.at(j))){
                if(j > distance){
                    distance = j;
                    furthest = requests.at(j);
                }
            }
        }

        occupied--;
        cache.erase(furthest);
        decisions.push_back(furthest);
    }

    return decisions;
}


