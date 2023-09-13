#include <iostream>
#include "Graph.h"

// constructor implementation
Graph::Graph()
{
    verticesNummber = 0;
    edgesNumber = 0;
}
// implementation of destructor
Graph::~Graph() {}

// implementation of addVertex
void Graph::addVertex(int vertex)
{
    if (adjancencyList.find(vertex) == adjancencyList.end())
    {
        adjancencyList[vertex] = std::vector<int>();
        verticesNummber++; // make sure to increase the number of vertices
    }
}
// implentaion of addEdge, this function creates edges between two vertices
void Graph::addEdge(int source, int destination)
{
    addVertex(source);
    addVertex(destination);

    adjancencyList[source].push_back(destination); // we use push.back because in fact we are adding to the vector
    adjancencyList[destination].push_back(source);
    edgesNumber++; // make sure to increase the number of edges
}
// implemetnation of edgeExist, we need to make sure if an edge exists or not
bool Graph::edgeExist(int source, int destination) const
{
    const auto it = adjancencyList.find(source);
    if (it != adjancencyList.end())
    {
        const std::vector<int> &neighboursVertex = it->second;
        for (int i = 0; i < neighboursVertex.size(); i++)
        {
            if (neighboursVertex[i] == destination) // this means the edge exits
            {
                return true;
            }
        }
    }
    return false;
}
// implementation of finsNeighbours
std::vector<int> Graph::findNeighbours(int vertex) const
{
    std::vector<int> notFoundedNeighbours;
    auto it = adjancencyList.find(vertex);
    if (it != adjancencyList.end())
    {
        return it->second;
    }
    else
    {
        return std::vector<int>();
    }
     return (it != adjancencyList.end()) ? it ->second: notFoundedNeighbours;
}
// impelemtaion of numberOfVertices
int Graph::numberOfVertices() const
{
    return verticesNummber;
}
// implementtion of numberOfEdges
int Graph::numberOfEdges() const
{
    return edgesNumber;
}
