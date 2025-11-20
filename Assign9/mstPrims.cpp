#include <iostream>
#include <vector>
#include <utility>
#include <queue>

int main(){
    int n,e;
    std::cin >> n >> e;

    std::vector<std::vector<std::pair<int,int>>> adjList(n + 1);

    for(int i = 0; i < e; i++){
        int u,v,w;
        std::cin >> u >> v >> w;

        adjList[v].push_back({u,w});
        adjList[u].push_back({v,w});
    }

    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> q;

    std::vector<bool> visited(n + 1, false);

    int cost = 0;

    q.push({0,1});

    int last = 1;

    while(!q.empty()){
        auto [wt,u] = q.top();
        q.pop();

        if(visited[u]) continue;

        cost += wt;

        visited[u] = true;

        for(auto &v : adjList[u]){
            if(!visited[v.first]){
                q.push({v.second,v.first});
            }
        }
    }

    std::cout << cost << std::endl;

}