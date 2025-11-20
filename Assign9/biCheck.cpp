#include <iostream>
#include <vector>
#include <string>
#include <queue>

bool isBipartiteUtil(int startNode, int n, 
                     const std::vector<std::vector<int>>& adjList, 
                     std::vector<int>& color) {
    
    std::queue<int> q;
    q.push(startNode);
    color[startNode] = 0; 

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adjList[u]) {
            if (color[v] == -1) {
                color[v] = 1 - color[u];
                q.push(v);
            } else if (color[v] == color[u]) {
                return false;
            }
        }
    }
    return true;
}

bool isBipartite(int n, const std::vector<std::vector<int>>& adjList) {
    std::vector<int> color(n + 1, -1);

    for (int i = 1; i <= n; i++) {
        if (color[i] == -1) {
            if (!isBipartiteUtil(i, n, adjList, color)) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int n, e;
    std::cout << "Enter the number of vertices (n) and edges (e): ";
    std::cin >> n >> e;

    std::vector<std::vector<int>> adjList(n + 1);

    std::cout << "Enter " << e << " undirected edges (format: u v):" << std::endl;
    for (int i = 0; i < e; i++) {
        int u, v;
        std::cin >> u >> v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    if (isBipartite(n, adjList)) {
        std::cout << "The graph is Bipartite." << std::endl;
    } else {
        std::cout << "The graph is not Bipartite." << std::endl;
    }

    return 0;
}