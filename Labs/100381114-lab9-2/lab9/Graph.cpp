#include <iostream>
#include "Graph.h"

Graph::Graph()
{
    verticesNummber=0;
    edgesNumber =0;
}

Graph::~Graph(){}

void Graph::addVertex (int vertex){
    if(adjancencyList.find(vertex)==adjancencyList.end()){
        adjancencyList[vertex]=std::vector<int>();
        verticesNummber++;
    }
}

void Graph::addEdge(int source, int destination){
    addVertex(source); //adding the first node to graph in case it doesn't exist yet
    addVertex(destination);// adding second node

    adjancencyList[source].push_back(destination);
    adjancencyList[destination].push_back(source);
    edgesNumber++;
}

bool Graph::edgeExist(int source, int destination)const{
     const auto it = adjancencyList.find(source);
      if(it !=adjancencyList.end()){
           const std::vector<int>& neighboursVertex = it->second;
           for(int i=0; i<neighboursVertex.size();i++){
            if(neighboursVertex[i]==destination ){
                return true ;
            }
           }


      }
         return false;

}

 std::vector<int> Graph::findNeighbours (int vertex)const{
    std::vector <int> notFoundedNeighbours;
    auto it = adjancencyList.find(vertex);
    if(it != adjancencyList.end()){
        return  it ->second;
    }
    else{
        return std::vector<int>();
    }
    return (it != adjancencyList.end()) ? it ->second: notFoundedNeighbours;
}

int Graph::numberOfVertices()const{
    return verticesNummber;
}

int Graph::numberOfEdges()const{
    return edgesNumber;
}
