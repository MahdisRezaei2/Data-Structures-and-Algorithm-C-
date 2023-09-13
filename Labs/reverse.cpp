#include<bits/stdc++.h>
using namespace std;

// Here we Create a pair of integer, which will be used in creating the adjancency list
typedef pair<int, int> myPairIntegers;

// Creating a Graph class, to create a graph object based on input from the file, and then implementing the reverse kruskal algorithm on the
// created Graph
class Graph
{
    int n; // number of vertices
    list<myPairIntegers> *adjancencyList;  // declaring the adjancency list we need to make the graph
    vector< pair<int, myPairIntegers> > edges; // creating a vector of pair and integer to use it to make the edges

public:
    Graph(int n); // Constructor

    // add edges to the graph
    void addEdge(int city1, int city2, int distance);

    // Find operation to find the parent and root of the node
    int find(vector<int>& parent, int city1);
    // union operation on two different sets
    void unionSets(vector<int>& parent, vector<int>& height, int city1, int city2);
    
    // reverseKruskal, which works in the opposite way of kruskal algorithm
    void reverseKruskal();
};

// implementaion of constructor 
Graph::Graph(int n)
{
    this->n = n;
    adjancencyList = new list<myPairIntegers>[n]; // creating the adjancency list based on the size n
}

// implemenation of the addEdge
void Graph::addEdge(int city1, int city2, int distance)
{   
    adjancencyList[city1].push_back({city2, distance});
    adjancencyList[city2].push_back({city1, distance});
    edges.push_back({distance, {city1, city2}});
}
// implemenation of the find function, recursively calling the function to find the parent
int Graph::find(vector<int>& parent, int city1)
{
    if (parent[city1] == city1)
        return city1; // if the node the same as its parent, then return the node , because that's the parent
    return parent[city1] = find(parent, parent[city1]); // if not, then recursively call find function to reach the parent
}

// implementation of the unionSets
void Graph::unionSets(vector<int>& parent, vector<int>& height, int city1, int city2)
{
    // fiRST, WE fnd the parents of two sets
    int parentOfU = find(parent, city1);
    int parentOfV = find(parent, city2);
 // we need to check which parent has the bigger height, to make sure that after unioning the sets we don't make a very long tree
    if (height[parentOfU] > height[parentOfV])
        parent[parentOfV] = parentOfU;
    else if (height[parentOfU] < height[parentOfV])
        parent[parentOfU] = parentOfV;
    else
    {
        parent[parentOfV] = parentOfU;
        height[parentOfU]++; // we need to make sure to increment the height for the parentOfU, because now parentOfU doen't have same height as
        // parentOfV like before
    }
}

// implementation of reverseKruskal
void Graph::reverseKruskal()
{
    // Sort edges in decreasing order based on the distance
    sort(edges.begin(), edges.end(), greater<pair<int, myPairIntegers>>());

    vector<int> parent(n); // this vector helps us to keep track of the parents of each node
    vector<int> height(n, 0); // this vector helps us to keep track of the heihg of the each node in fact the parents, to help us avoiding creating
    // very long trees
    // first we set the parent of each node to the node , in other words each node is its own parent first
    for (int i = 0; i < n; i++)
        parent[i] = i;

    int distanceOfMST = 0; // Initialize distance to 0

    cout << "Edges in MST: " <<endl;

    // going through all edges to see which edges we need to remove and which one to keep
    for (int i=0; i < edges.size(); i++)
    {
        int city1 = edges[i].second.first;
        int city2 = edges[i].second.second;
        int distance = edges[i].first;

        // Remove edge 
        adjancencyList[city1].remove({city2, distance});
        adjancencyList[city2].remove({city1, distance});

        // we need to check if we remove an edge it won't make the graph disconnected 
        int parentOfU = find(parent, city1);
        int parentOfV = find(parent, city2);
        if (parentOfU != parentOfV)
        {
            unionSets(parent, height, city1, city2);
            // edge is part of the graph
            cout << "(" << city1 << " -> " << city2 << ") - Distance: " << distance << " - Added to MST "<<endl;
            distanceOfMST += distance;
        }
        else
        {
            // edge is removed
            cout << "(" << city1 << " -> " << city2 << ") - Distance: " << distance << " - Removed"<<endl;
        }
    }

    cout << "Total distance of MST is: " << distanceOfMST;
}


// main
int main()
{  
     // reading the inout from the file 
    ifstream inputFile("sparce7.txt");
    if (!inputFile)
    {   // the name is not correct, let the user know
        cout << "File name is not correct." << endl;
        return 1;
    }

    int n; // Number of nodes in the graph, first line of the file shows the number of node
    inputFile >> n;  // storing thr value in varaible
    Graph g(n);  // creating graph based on this number of nodes

    // declaring the valribles we need 
    int city1, city2, distance; 
   /**
    *getting the data from the file, storing them in the varaibles
    * continue reading till file has data
   */
    while (inputFile >> city1 >> city2 >> distance)
    {  
        //calling the addEdge function to add edges to the graph and create the graph
        g.addEdge(city1, city2, distance);
    }
  
  // closing the file
    inputFile.close();
  
  // now that we have the necessary data, we can call the reverseKruskal function 
    g.reverseKruskal();
    return 0;
}
