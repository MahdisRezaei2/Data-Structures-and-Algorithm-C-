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
    ~Graph(); // Destructor
    // We need to have a struct for weighting
    struct WeightingEdges
    {
        int destinitaion;
        int weight;
        // this is the constructor
        WeightingEdges(int destini, int wei)
        {
            destinitaion = destini;
            weight = wei;
        }
    };

    void addVertex(int vertex);                        // to add vertexes to the graph
    void addEdge(int source, int destination);         // to add edges to the graph
    bool edgeExist(int source, int destination) const; // this funtion makes sure if an edge exists
    std::vector<int> findNeighbours(int vertex) const; // we need to find the neighbours of an vertex
    int numberOfVertices() const;                      // find the number of vetices of a graph
    int numberOfEdges() const;                         // find number of edges of a graph
    int getWeight(int source, int destination) const;  // i made this funtion, but didn't need it in fact
    // void gettingWeight(int source, int destination, int weight);

private:
    std::unordered_map<int, std::vector<int>> adjancencyList; // need this for making the UDWG
    // std::unordered_map<std::pair<int,int>,int> getedgesWeight;
    int verticesNummber;
    int edgesNumber;
};

#endif