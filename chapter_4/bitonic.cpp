#include <bits/stdc++.h>
/*creditos ao claudson*/

using namespace std;

double distance(pair<double,double> a, pair<double,double> b){
    double dx2 = (b.first - a.first)*(b.first - a.first);
    double dy2 = (b.second - a.second)*(b.second - a.second);
    return sqrt(dx2 + dy2);
}

double bitonic_tour(vector<pair<double,double>> points){ /*suppose the points are ordered*/
    if(points.size() < 3) return 0;
    
    int tam = points.size();
    vector<vector<double>> c(tam);//caminhos
    vector<vector<double>> d(tam);//distancias
    for(int i = 0; i < tam; i++){
        c.at(i).resize(tam);
        d.at(i).resize(tam);
    }

    for(int i = 0; i < tam; i++){
        for(int j = i; j < tam; j++){
            double dist = distance(points.at(i),points.at(j));
            d.at(i).at(j) = dist;
            d.at(j).at(i) = dist;
        }
    }
    

    c.at(0).at(1) = d.at(0).at(1);
    
    for(int i = 2; i < tam; i++){
        for(int j = 0; j < i-1; j++){
            c.at(j).at(i) = c.at(j).at(i-1) + d.at(i-1).at(i);
        }
        c.at(i-1).at(i) = INT32_MAX;
        for(int k = 0; k < i-1; k++){
            double sum = c.at(k).at(i-1) + d.at(k).at(i);
            if(sum < c.at(i-1).at(i)){
                c.at(i-1).at(i) = sum;
            }
        }
    }

    return c.at(tam - 2).at(tam - 1) + d.at(tam - 2).at(tam - 1);
}


int main(void){
    vector<pair<double,double>> p = {{0,6},{1,0},{2,3},{5,4},{6,1},{7,5},{8,2}};
    std::cout << bitonic_tour(p) << std::endl;
    return 0;
}