#include <iostream>
#include <vector>
#include <stack>

void topoSort(int curr, const std::vector<std::vector<int>>& adjList, std::vector<bool>& visited, std::stack<int>& rec){
    visited[curr] = true;

    for(auto neighbour : adjList[curr]){
        if(!visited[neighbour]){
            topoSort(neighbour, adjList, visited, rec);
        }
    }
    rec.push(curr);
}

int main(){
    int n,e;
    std::cin >> n >> e;

    std::vector<std::vector<int>> adjList(n + 1);

    for(int i = 0; i < e; i++){
        int u,v;
        std::cin >> u >> v;

        adjList[u].push_back(v);
    }

    std::vector<bool> visited(n + 1,false);
    std::stack<int> rec;

    for(int i = 1; i < n + 1; i++){
        if(!visited[i])
            topoSort(i,adjList,visited,rec);
    }

    while (!rec.empty()) {
        std::cout << rec.top() << ' ';
        rec.pop();
    }
    std::cout << std::endl;

}