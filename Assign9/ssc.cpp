#include <iostream>
#include <vector>
#include <string>
#include <stack>

void dfsFirstPass(int u, const std::vector<std::vector<int>>& adjList,
                  std::vector<bool>& visited, std::stack<int>& finishStack) {
    visited[u] = true;
    for (int v : adjList[u]) {
        if (!visited[v]) {
            dfsFirstPass(v, adjList, visited, finishStack);
        }
    }
    finishStack.push(u);
}

void dfsSecondPass(int u, const std::vector<std::vector<int>>& adjList_T,
                   std::vector<bool>& visited, std::vector<int>& currentSCC) {
    visited[u] = true;
    currentSCC.push_back(u);
    for (int v : adjList_T[u]) {
        if (!visited[v]) {
            dfsSecondPass(v, adjList_T, visited, currentSCC);
        }
    }
}

std::vector<std::vector<int>> getTranspose(int n, const std::vector<std::vector<int>>& adjList) {
    std::vector<std::vector<int>> adjList_T(n + 1);
    for (int u = 1; u <= n; u++) {
        for (int v : adjList[u]) {
            adjList_T[v].push_back(u);
        }
    }
    return adjList_T;
}

void printSCCs(int n, const std::vector<std::vector<int>>& adjList) {
    std::stack<int> finishStack;
    std::vector<bool> visited(n + 1, false);

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfsFirstPass(i, adjList, visited, finishStack);
        }
    }

    std::vector<std::vector<int>> adjList_T = getTranspose(n, adjList);

    std::fill(visited.begin(), visited.end(), false);

    std::cout << "Strongly Connected Components:" << std::endl;
    while (!finishStack.empty()) {
        int u = finishStack.top();
        finishStack.pop();

        if (!visited[u]) {
            std::vector<int> currentSCC;
            dfsSecondPass(u, adjList_T, visited, currentSCC);
            
            for (int node : currentSCC) {
                std::cout << node << " ";
            }
            std::cout << std::endl;
        }
    }
}

int main() {
    int n, e;
    std::cout << "Enter the number of vertices (n) and edges (e): ";
    std::cin >> n >> e;

    std::vector<std::vector<int>> adjList(n + 1);

    std::cout << "Enter " << e << " directed edges (format: u v for u -> v):" << std::endl;
    for (int i = 0; i < e; i++) {
        int u, v;
        std::cin >> u >> v;
        adjList[u].push_back(v);
    }

    printSCCs(n, adjList);

    return 0;
}