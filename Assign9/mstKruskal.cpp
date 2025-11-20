#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

class DS{
    std::vector<int> parent, rank;
public:
    DS(int n){
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 1;
        }
    }
    int find(int i) {
        return (parent[i] == i) ? i : (parent[i] = find(parent[i]));
    }

    void unite(int x, int y) {
        int s1 = find(x), s2 = find(y);
        if (s1 != s2) {
            if (rank[s1] < rank[s2]) parent[s1] = s2;
            else if (rank[s1] > rank[s2]) parent[s2] = s1;
            else parent[s2] = s1, rank[s1]++;
        }
    }
};

bool cmp(const std::vector<int>& a, const std::vector<int>& b){
    return a[2] < b[2];
}

int main(){
    int n, e;
    std::cin >> n >> e;

    std::vector<std::vector<int>> edges(e,std::vector<int>(3,-1));
    std::vector<std::vector<std::pair<int,int>>> adjList(n+1);

    for(int i = 0; i < e; i++){
        int u,v,w;
        std::cin >> u >> v >> w;
        edges[i] = {u,v,w};
    }

    std::sort(edges.begin(),edges.end(),cmp);

    DS ds(n);

    int cost = 0, count = 0;

    for(auto &e : edges){
        int u = e[0], v = e[1], w = e[2];

        if (ds.find(u) != ds.find(v)) {
            ds.unite(u, v);
            adjList[u].push_back({v,w});
            adjList[v].push_back({u,w});
            cost += w;
            if (++count == n - 1) break;
        }
    }

    std::cout << cost << std::endl;

    std::cout << "Adjacency List" << std::endl;    
    for(int i = 1; i < n + 1; i++){
        std::cout << i << " : ";
        for(auto neighbour : adjList[i]){
            std::cout << "{" <<neighbour.first << "," << neighbour.second<<"}" << ",";
        }
        std::cout << std::endl;
    }



}
