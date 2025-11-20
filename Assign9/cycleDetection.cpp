#include <iostream>
#include <vector>
#include <string>

bool isCyclicUndirectedUtil(int u, int parent, 
                            const std::vector<std::vector<int>>& adjList, 
                            std::vector<bool>& visited) {
    visited[u] = true;

    for (int v : adjList[u]) {
        if (!visited[v]) {
            if (isCyclicUndirectedUtil(v, u, adjList, visited)) {
                return true;
            }
        }
        else if (v != parent) {
            return true;
        }
    }
    return false;
}

bool isCyclicUndirected(int n, const std::vector<std::vector<int>>& adjList) {
    std::vector<bool> visited(n + 1, false);

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            if (isCyclicUndirectedUtil(i, -1, adjList, visited)) {
                return true;
            }
        }
    }
    return false;
}

bool isCyclicDirectedUtil(int u, 
                          const std::vector<std::vector<int>>& adjList,
                          std::vector<bool>& visited, 
                          std::vector<bool>& recStack) {
    visited[u] = true;
    recStack[u] = true;

    for (int v : adjList[u]) {
        if (!visited[v]) {
            if (isCyclicDirectedUtil(v, adjList, visited, recStack)) {
                return true;
            }
        }
        else if (recStack[v]) {
            return true;
        }
    }
    
    recStack[u] = false;
    return false;
}

bool isCyclicDirected(int n, const std::vector<std::vector<int>>& adjList) {
    std::vector<bool> visited(n + 1, false);
    std::vector<bool> recStack(n + 1, false);

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            if (isCyclicDirectedUtil(i, adjList, visited, recStack)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int n, e;
    std::cin >> n >> e;

    std::vector<std::vector<int>> adjList(n + 1);
    std::string graphType;

    std::cout << "Is the graph 'directed' or 'undirected'? ";
    std::cin >> graphType;

    for (int i = 0; i < e; i++) {
        int u, v;
        std::cin >> u >> v;

        adjList[u].push_back(v);

        if (graphType == "undirected") {
            adjList[v].push_back(u);
        }
    }

    bool hasCycle = false;
    if (graphType == "directed") {
        hasCycle = isCyclicDirected(n, adjList);
    } else if (graphType == "undirected") {
        hasCycle = isCyclicUndirected(n, adjList);
    } else {
        std::cerr << "Error: Invalid graph type entered." << std::endl;
        return 1; 
    }

    if (hasCycle) {
        std::cout << "The graph contains a cycle." << std::endl;
    } else {
        std::cout << "The graph does not contain a cycle." << std::endl;
    }

    return 0;
}