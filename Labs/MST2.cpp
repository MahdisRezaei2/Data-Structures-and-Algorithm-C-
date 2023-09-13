#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class UnionFind {
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int x) {
        if (x != parent[x])
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unionNodes(int x, int y) {
        int root_x = find(x);
        int root_y = find(y);

        if (root_x == root_y)
            return false;

        if (rank[root_x] > rank[root_y])
            parent[root_y] = root_x;
        else if (rank[root_x] < rank[root_y])
            parent[root_x] = root_y;
        else {
            parent[root_y] = root_x;
            rank[root_x]++;
        }

        return true;
    }
};

struct Edge {
    int city1;
    int city2;
    int distance;

    Edge(int c1, int c2, int dist) : city1(c1), city2(c2), distance(dist) {}
};

bool compareEdges(const Edge& e1, const Edge& e2) {
    return e1.distance > e2.distance;
}

void reverseKruskal(const std::string& input_file) {
    std::ifstream file(input_file);
    int num_nodes;
    file >> num_nodes;

    std::vector<Edge> edges;
    int city1, city2, distance;
    while (file >> city1 >> city2 >> distance) {
        edges.emplace_back(city1, city2, distance);
    }
    file.close();

    // Sort edges in reverse order of distance (highest to lowest)
    std::sort(edges.begin(), edges.end(), compareEdges);

    UnionFind uf(num_nodes);

    std::vector<Edge> mst_edges;
    int mst_distance = 0;

    std::cout << "Removed edges:" << std::endl;
    for (const auto& edge : edges) {
        if (uf.unionNodes(edge.city1 - 1, edge.city2 - 1)) {
            mst_edges.push_back(edge);
            mst_distance += edge.distance;
        } else {
            std::cout << edge.city1 << " - " << edge.city2 << " (Distance: " << edge.distance << ")" << std::endl;
        }
    }

    std::cout << std::endl << "Minimum Spanning Tree:" << std::endl;
    for (const auto& edge : mst_edges) {
        std::cout << edge.city1 << " - " << edge.city2 << std::endl;
    }

    std::cout << std::endl << "Total Distance of MST: " << mst_distance << std::endl;
}

int main() {
    reverseKruskal("sparce7.txt"); // Replace with the actual path to your input file
    return 0;
}
