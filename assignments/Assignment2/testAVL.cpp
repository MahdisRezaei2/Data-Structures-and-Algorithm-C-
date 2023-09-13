#include "BST.h"
#include "AVL.h"
#include <fstream>
#include <iostream>

int main()
{
    std::cout << "please enter file name "<<std::endl;
    std::string fileName;
    std::cin >> fileName;
    AVL<int> *avl = buildAVLTree<int>(fileName);
    std::cout << "height of AVL tree is:" << avl->height() << std::endl;
    printAVL(avl);
    std::cout << "Enter an integer value to insert: ";
    int node;
    std::cin >> node;
    insertNodeAVL(avl, node);
    std::cout << "height of AVL tree is:" << avl->getRoot()->getHeight() << std::endl;
    printAVL(avl);
    std::cout << "Enter an integer value to delete: ";
    std::cin >> node;
    deleteNodeAVL(avl, node);
    std::cout << "height of AVL tree is:" << avl->getRoot()->getHeight() << std::endl;
    printAVL(avl);
    deleteAVLTree(avl);
    printAVL(avl);

    return 0;
}
