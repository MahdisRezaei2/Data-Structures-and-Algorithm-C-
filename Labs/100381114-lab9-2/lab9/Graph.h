#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>
#include <unordered_map>

class Graph
{

public:
    // Constructor
    Graph();
    ~Graph();
    struct WeightingEdges
    {
        int destinitaion;
        int weight;

        WeightingEdges(int destini, int wei)
        {
            destinitaion = destini;
            weight = wei;
        }
    };


    void addVertex(int vertex);
    void addEdge(int source, int destination);
    bool edgeExist(int source, int destination) const;
    std::vector<int> findNeighbours(int vertex) const;
    int numberOfVertices() const;
    int numberOfEdges() const;
    int getWeight(int source, int destination)const;
    //void gettingWeight(int source, int destination, int weight);

private:
    std::unordered_map<int, std::vector<int>> adjancencyList;
   // std::unordered_map<std::pair<int,int>,int> getedgesWeight;
    int verticesNummber;
    int edgesNumber;
    
};

#endif