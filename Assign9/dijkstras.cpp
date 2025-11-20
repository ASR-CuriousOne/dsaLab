#include <iostream>
#include <vector>
#include <utility>
#include <limits>
#include <queue>

int main(){
    int n, e;
    std::cin >> n >> e;

    std::vector<std::vector<std::pair<int,int>>> adjList(n + 1);

    for(int i = 0; i < e; i++){
        int u,v,w;
        std::cin >> u >> v >> w;

        adjList[u].push_back({v,w});
    }
    int source;
    std::cin >> source;

    std::vector<int> dist(n+1,INT_MAX);
    dist[source] = 0;

    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> q;
    q.push({0,source});

    while(!q.empty()){
        int curr = q.top().second;
        q.pop();

        for(auto neighbours : adjList[curr]){
            auto [v,edgeWeight] = neighbours;

            if(dist[v] > dist[curr] + edgeWeight){
                dist[v] = dist[curr] + edgeWeight;
                q.push({dist[v],v});
            }
        }
    }

    for(int i = 1; i < n + 1; i++){
        std::cout << i << " : " << dist[i] << " , " ; 
    }
    std::cout << std::endl;




}