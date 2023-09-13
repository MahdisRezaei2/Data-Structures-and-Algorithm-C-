#include <iostream>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <fstream>
#include "Graph.h"
#include "Graph.cpp"

// we need this function to generate random numbers for number of edges
int generateRandomNumbers(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

// ijmplementaion of makeSparseUDWG function
std::unordered_map<int, std::vector<Graph::WeightingEdges>> makeSparseUDWG(int n, const Graph &graphObj)
{
    std::unordered_map<int, std::vector<Graph::WeightingEdges>> graph;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < n; i++)
    {
        graph[i] = std::vector<Graph::WeightingEdges>();
    }

    int maxNumberOfEdges = 2 * n;
    int numberOfEdges = generateRandomNumbers(0, maxNumberOfEdges) + 1;

    for (int i = 0; i < numberOfEdges; i++)
    {
        int source = generateRandomNumbers(0, n - 1);
        int destination = generateRandomNumbers(0, n - 1);
        int weight = generateRandomNumbers(1, 100);

        while (source == destination || graphObj.edgeExist(source, destination))
        {
            source = generateRandomNumbers(0, n - 1);
            destination = generateRandomNumbers(0, n - 1);
        }
        graph[source].push_back(Graph::WeightingEdges(destination, weight));
        graph[destination].push_back(Graph::WeightingEdges(source, weight));
    }

    return graph;
}
// implementaion of makeDenseDWG function
std::vector<std::vector<int>> makeDenseDWG(int n)
{
    std::vector<std::vector<int>> adjacencyMatrix(n, std::vector<int>(n, 0));
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int maxNumberOfEdges = ((n - 2) * n) / 2;
    int numberOfEdges = generateRandomNumbers(0, maxNumberOfEdges) + 1;

    for (int i = 0; i < numberOfEdges; i++)
    {
        int source = generateRandomNumbers(0, n - 1);
        int destination = generateRandomNumbers(0, n - 1);
        int weight = generateRandomNumbers(1, 100);

        while (source == destination || adjacencyMatrix[source][destination] != 0)
        {
            source = generateRandomNumbers(0, n - 1);
            destination = generateRandomNumbers(0, n - 1);
        }
        adjacencyMatrix[source][destination] = weight;
        adjacencyMatrix[destination][source] = weight;
    }
    return adjacencyMatrix;
}
// implementaion fo printGraph function to print the sparse function in a file
void printGraph(std::unordered_map<int, std::vector<Graph::WeightingEdges>> graph, const std::string &fileName, int n)
{

    std::ofstream outputFile(fileName);
    if (!outputFile)
    {
        std::cerr << "Erro:couldn't open the file" << fileName << std::endl;
        return;
    }

    outputFile << n << std::endl;
    for (const auto &inputOfGraph : graph)
    {
        int source = inputOfGraph.first;
        const auto &neighbours = inputOfGraph.second;
        for (const auto &neighbour : neighbours)
        {
            int destination = neighbour.destinitaion;
            int weight = neighbour.weight;
            outputFile << source << "-> " << destination << " weight: " << weight << std::endl;
        }
    }
    outputFile.close();
}
// main
int main()
{
    int n = 12;
    Graph graphObj;

    std::unordered_map<int, std::vector<Graph::WeightingEdges>> graph = makeSparseUDWG(n, graphObj);
    printGraph(graph, "sparse25.txt", n);
    std::cout << "Number of nodes (n): " << n << std::endl;

    // print the sparse graph in console
    for (const auto &vertex : graph)
    {
        int vertexNumber = vertex.first;
        const auto &edges = vertex.second;

        std::cout << "source -> " << vertexNumber << " ";

        for (const auto &edge : edges)
        {
            int destinitaion = edge.destinitaion;
            int weight = edge.weight;

            std::cout << " destination: " << destinitaion << ", "
                      << "weight: " << weight;
        }
        std::cout << std::endl;
    }
    // print the dense graph in console
    std::vector<std::vector<int>> denseGraph = makeDenseDWG(n);
    std::cout << " the dense graph: " << std::endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << denseGraph[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
