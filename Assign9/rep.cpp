#include <iostream>
#include <vector>
#include <exception>

int main(){

    int n,e;
    std::cin >> n >> e;

    if(e < n - 1 || e > n * (n-1)/2){
        throw std::runtime_error("Invalid number of edge for the number of vertices.");
    }

    std::vector<std::vector<int>> adjMatrix(n + 1,std::vector<int>(n + 1,0));
    std::vector<std::vector<int>> adjList(n + 1);

    for(int i = 0; i < e; i++){
        int u,v;
        std::cin >> u >> v;

        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;

        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    std::cout << "Adjacency Matirx" << std::endl;

    for(int i = 0; i < n + 1; i++){
        std::cout << "| ";
        for(int j = 0; j < n + 1; j++){
            if(i == 0) std::cout << j << " | ";
            else if(j == 0) std::cout << i << " | ";
            else std::cout << adjMatrix[i][j] << " | ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Adjacency List" << std::endl;    
    for(int i = 1; i < n + 1; i++){
        std::cout << i << " : ";
        for(auto neighbour : adjList[i]){
            std::cout << neighbour << ",";
        }
        std::cout << std::endl;
    }
}