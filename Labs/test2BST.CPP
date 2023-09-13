#include "BST.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// This function gets the input from the user and assign it to n1
int getInput()
{
    int n1;
    std::cout << "please enter a non-negative integer, which will be the number of numbers" << std::endl;
    std::cin >> n1;
    return n1;
}

// This function generates a list of n random integers from [-n,n], by pushing the value of random integers into a vector
std::vector<int> genData(int n)
{
    int min = -n;
    int max = n;
    int size = n;
    std::vector<int> list;
    srand(time(NULL));
    int random;
    for (int i = 0; i < size; i++)
    {
        random = rand() % (max - min + 1) + min;
        list.push_back(random);
    }

    return list;
}

// This function prints the list we created in the genData() function
void printList(std::vector<int> &list1)
{
    int size = list1.size();
    for (int i = 0; i < size; i++)
    {
        std::cout << list1[i] << " ";
    }
    std::cout << std::endl;
}

//This function creates a binary search tree based on the data we stored in the list in the genData function 
BST<int> &makeBST(std::vector<int> &list1)
{

    BST<int> *listToBST = new BST<int>();

    for (int i = 0; i < list1.size(); i++)
    {
        listToBST->insert(list1[i]);
    }
    return *listToBST;
}

// This function print the binary search tree we created in the makeBST function, by calling inorder or preorder methods of the BST class
void printBT(BST<int> &bst1)
{   
    // For testing we can either comment inorder or preorder and try calling the other one
    bst1.inorder(bst1.getRoot());
    // bst1.preorder(bst1.getRoot());
}

//This function trys to find the height of the binary search tree
int height(BSTNode<int> *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    else
    {

        int lHeight = height(node->getLeft());
        int rHeight = height(node->getRight());

        if (lHeight > rHeight)
            return (lHeight + 1);
        else
            return (rHeight + 1);
    }
}
//for implementing the height function, I used a heper function to call the height function 
int height(BST<int> &bst1)
{
    return height(bst1.getRoot());
}

// Main method 
int main()
{

    int n1;

    n1 = getInput();
    std::vector<int> list1 = genData(n1);
    std::cout << "The List1: " << std::endl;
    printList(list1);
    BST<int> &bst1 = makeBST(list1);
    std::cout << "The BST1: " << std::endl;
    printBT(bst1);
    std::cout << std::endl;
    std::cout << "The height of bst1 is " << height(bst1) << std::endl;
    delete &bst1;

    return 0;
}