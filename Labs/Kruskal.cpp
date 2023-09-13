#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int src, dest, weight;
};

struct DisjointSet {
    vector<int> parent, rank;
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }
    int find(int u) {
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }
    void merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (rank[u] > rank[v])
            parent[v] = u;
        else {
            parent[u] = v;
            if (rank[u] == rank[v])
                rank[v]++;
        }
    }
};

bool compareEdges(const Edge &e1, const Edge &e2) {
    return e1.weight < e2.weight;
}

vector<Edge> kruskalMST(vector<Edge> &edges, int V) {
    sort(edges.begin(), edges.end(), compareEdges);

    vector<Edge> mst;
    DisjointSet ds(V);

    for (const Edge &e : edges) {
        int srcParent = ds.find(e.src);
        int destParent = ds.find(e.dest);
        if (srcParent != destParent) {
            mst.push_back(e);
            ds.merge(srcParent, destParent);
        }
    }

    return mst;
}

int main() {
    int V = 6; // Number of vertices
    int E = 9; // Number of edges

    vector<Edge> edges = {
        {0, 1, 4}, {0, 2, 3}, {1, 2, 2},
        {1, 3, 1}, {1, 4, 2}, {2, 3, 4},
        {3, 4, 3}, {3, 5, 2}, {4, 5, 5}
    };

    vector<Edge> mst = kruskalMST(edges, V);

    cout << "Minimum Spanning Tree edges:" << endl;
    for (const Edge &e : mst) {
        cout << e.src << " - " << e.dest << " : " << e.weight << endl;
    }

    return 0;
}
