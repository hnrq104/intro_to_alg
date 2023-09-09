#include <bits/stdc++.h>
#include "basic.hpp"

using namespace std;

/*
FORD-FULKERSON-METHOD(G,s,t)
1   initialize flow f to 0
2   while there exists an augmenting path p in the residual network Gf
3       augment flow along p
4   return f
*/

/*Edmonds-Karp (use bfs to find shortest (all edges are unit weighted) paths)*/


/*WILL USE MATRICES, USING LINKED LISTS IS MORE EFFICIENT BUT IM LAZY RN*/


/*returns a path*/
vector<int> bfs_matrix(vector<vector<double>> Gf, int source, int sink){
    std::queue<int> order;
    std::vector<bool> visited(Gf.size(),false);
    vector<int> path(Gf.size(),-1);

    order.push(source);
    visited.at(source) = true;
    while(!order.empty()){
        int vertex = order.front();
        order.pop();

        for(uint i = 0; i < Gf.size(); i++){
            if(Gf.at(vertex).at(i) != 0 && !visited.at(i)){
                path.at(i) = vertex;
                visited.at(i) = true;
                order.push(i);
            }
        }
    }

    return path;
}


double  ford_fulkerson(vector<vector<double>> &capacities, int source, int sink){
    int n = capacities.size();
    vector<vector<double>> flow(n,vector<double>(n,0));
    vector<vector<double>> Gf(capacities);
    while(1){
        vector<int> path = bfs_matrix(Gf,source,sink);
        if(path.at(sink) == -1) break;

        double c_min = DBL_MAX;
        int edge = sink;
        while(edge != source){
            /*in Gf (u,v) + (v,u) = Capacity(u,v)*/
            int cap = Gf.at(path.at(edge)).at(edge);
            if(c_min < cap){
                c_min = cap;
            }
            edge = path.at(edge);
        }

        edge = sink;
        while(edge != source){
            if(capacities.at(path.at(edge)).at(edge)){
                flow.at(path.at(edge)).at(edge) += c_min;

            }
            else{
                flow.at(path.at(edge)).at(edge) -= c_min;    
            }
            
            Gf.at(path.at(edge)).at(edge) += c_min;
            Gf.at(edge).at(path.at(edge)) -= c_min;

            edge = path.at(edge);
        }
        /*do the same now but decreasing*/
    }



    /*return what we need*/
    double sum = 0;
    for(int i = 0; i < n; i++){
        sum += flow.at(source).at(i);
    }
    return sum;
}