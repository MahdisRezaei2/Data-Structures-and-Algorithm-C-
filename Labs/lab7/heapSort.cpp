#include <iostream>
#include <string>
#include <vector>
#include <cmath>

// Heapifying the subtree rooted at 'root
void heapify(std::vector<int> &data, int size, int root)
{
    int largest = root;
    int leftChildIndex = (2 * root) + 1;  /*left child index*/
    int rightChildIndex = (2 * root) + 2; /*right child index*/

    // If the left child is bigger than the root
    if ((leftChildIndex < size) && data[leftChildIndex] > data[largest])
        largest = leftChildIndex;

    // If the right child is bigger than the root
    if ((rightChildIndex < size) && data[rightChildIndex] > data[largest])
        largest = rightChildIndex;

    // If root is not the largest anymore, swap it
    if (largest != root)
    {
        std::swap(data[root], data[largest]);
        heapify(data, size, largest); //Calling the function recursively to make sure all subtrees are heapified
    }
}

// This function implements bottom-up approach to construct heap from the token array
void bottomUp(std::vector<int> &data)
{
    int n = data.size();

    // we need to start from the last non-leaf node and heapify
    for (int i = (n / 2) - 1; i >= 0; i--)
        heapify(data, n, i);
}

// Perform Heap Sort on the created max heap

void heapSort(std::vector<int> &data)
{
    int n = data.size();

    // Build the Max Heap
    bottomUp(data);

    // swap the element with the last element of the array (heap)
    for (int i = n - 1; i > 0; i--)
    {
        std::swap(data[0], data[i]);
        heapify(data, i, 0);
    }
}
int main()
{
    // Array of int
    std::vector<int> data = {3, 19, 1, 14, 8, 7};

    // Calling heapsort function
    heapSort(data);
    // Printing the sorted array
    std::cout << " Array after Heap Sort: ";
    for (int i = 0; i < data.size(); i++)
    {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}