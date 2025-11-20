#include <iostream>
#include <vector>
#include <stack>

int main(){
    int n,e;
    std::cin >> n >> e;

    std::vector<std::vector<int>> adjList(n + 1);

    for(int i = 0; i < e; i++){
        int u,v;
        std::cin >> u >> v;

        adjList[v].push_back(u);
        adjList[u].push_back(v);
    }

    std::vector<bool> visited(n+1,false);

    std::stack<int> dfs;

    int source;

    std::cin >> source;

    dfs.push(source);
    visited[source] = true;

    while(!dfs.empty()){
        int curr = dfs.top();
        dfs.pop();

        std::cout << curr << ' ';

        for(auto neighbour : adjList[curr]){
            if(!visited[neighbour]){
                visited[neighbour] = true;
                dfs.push(neighbour);
            }
        }
        
    }
    std::cout << std::endl;
}