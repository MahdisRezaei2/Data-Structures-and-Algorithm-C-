#ifndef AVL_H
#define AVL_H
#include <iostream>
#include <fstream>
#include "BST.h"
// *&node     *node
template <typename T>

class AVL : public BST<T>
{

public:
  void insert(const T &elm);
  void deleteByCopying(BSTNode<T> *&node);
  bool checkBalance() const;
  BSTNode<T> *getRoot() const;
  void setRoot(BSTNode<T> *p);
  int computeHeight(BSTNode<T> *p) const;
  int height() const;
  BSTNode<T> *rotateRight(BSTNode<T> *p);
  BSTNode<T> *rotateLeftRight(BSTNode<T> *p);
  BSTNode<T> *rotateLeft(BSTNode<T> *p);
  BSTNode<T> *rotateRightLeft(BSTNode<T> *p);

private:
  void updateHeight(BSTNode<T> *p);

  BSTNode<T> *balance(BSTNode<T> *p);

  BSTNode<T> *insert(const T &elm, BSTNode<T> *p);
  bool checkBalance(BSTNode<T> *p) const;

  BSTNode<T> *root;
};
template <typename T>
BSTNode<T> *AVL<T>::getRoot() const
{
  return root;
}
template <typename T>
void AVL<T>::setRoot(BSTNode<T> *p)
{
  root = p;
}
// insert function
template <typename T>
void AVL<T>::insert(const T &elm)
{
  this->root = insert(elm, this->root);
  // checkBalance(this->root);
}

// insert helper function
template <typename T>
BSTNode<T> *AVL<T>::insert(const T &elm, BSTNode<T> *p)
{
  // std::cout << "hi insert";
  if (p == nullptr)
    // std::cout << "hi from insert 2";
    return new BSTNode<T>(elm);
  if (elm < p->getElm())
  {
    // std::cout << "hi from left ";
    p->setLeft(insert(elm, p->getLeft()));
  }
  else
    p->setRight(insert(elm, p->getRight()));

  updateHeight(p); // to update the hight of each node during recursive insertion, so the hight information will be accurate when want to balance the tree
  // std::cout << "hi from insert 3";

  return balance(p); // need to call the balance function, to make sure after inserting the new node AVL Tree is balanced
}

// deleteByCopying implementation
template <typename T>
void AVL<T>::deleteByCopying(BSTNode<T> *&node)
{

  // call the deleteByCopying function from the BST class
  BST<T>::deleteByCopying(node);

  // check balance
  checkBalance(this->getRoot());
}

// Left rotation implementation
template <typename T>
BSTNode<T> *AVL<T>::rotateLeft(BSTNode<T> *p)
{
  BSTNode<T> *newRoot = p->getRight();
  p->setRight(newRoot->getLeft());
  newRoot->setLeft(p);
  updateHeight(p);
  updateHeight(newRoot);
  return newRoot;
}

// Right rotation implementation
template <typename T>
BSTNode<T> *AVL<T>::rotateRight(BSTNode<T> *p)
{
  BSTNode<T> *newRoot = p->getLeft();
  p->setLeft(newRoot->getRight());
  newRoot->setRight(p);
  updateHeight(p);
  updateHeight(newRoot);
  return newRoot;
}

// Left-Right rotation implementation
template <typename T>
BSTNode<T> *AVL<T>::rotateLeftRight(BSTNode<T> *p)
{
  p->setLeft(rotateLeft(p->getLeft()));
  return rotateRight(p);
}

// Right-left rotation implementation
template <typename T>
BSTNode<T> *AVL<T>::rotateRightLeft(BSTNode<T> *p)
{
  p->setRight(rotateRight(p->getRight()));
  return rotateLeft(p);
}

// Make a node balance
template <typename T>
BSTNode<T> *AVL<T>::balance(BSTNode<T> *p)
{
  if (p == nullptr)
    return nullptr;

  if (computeHeight(p->getLeft()) - computeHeight(p->getRight()) > 1)
  {
    if (computeHeight(p->getLeft()->getLeft()) >= computeHeight(p->getLeft()->getRight()))
      p = rotateRight(p);
    else
    {
      p->setLeft(rotateLeft(p->getLeft()));
      p = rotateRight(p);
    }
  }
  else if (computeHeight(p->getRight()) - computeHeight(p->getLeft()) > 1)
  {
    if (computeHeight(p->getRight()->getRight()) >= computeHeight(p->getRight()->getLeft()))
      p = rotateLeft(p);
    else
    {
      p->setRight(rotateRight(p->getRight()));
      p = rotateLeft(p);
    }
  }
  updateHeight(p);
  return p;
}

// Check balance
template <typename T>
bool AVL<T>::checkBalance() const
{
  return checkBalance(this->root);
}
template <typename T>
bool AVL<T>::checkBalance(BSTNode<T> *p) const
{

  if (p == nullptr)
  {
    return true;
  }
  else
  {
    int balanceFactor = computeHeight(p->getLeft()) - computeHeight(p->getRight());
    if (balanceFactor < -1 || balanceFactor > 1)
      return false;
    return checkBalance(p->getLeft()) && checkBalance(p->getRight());
  }
}
template <typename T>
int AVL<T>::computeHeight(BSTNode<T> *p) const
{
  if (p == nullptr)
    return -1;
  return p->getHeight();
}
template <typename T>
void AVL<T>::updateHeight(BSTNode<T> *p)
{
  p->setHeight(std::max(computeHeight(p->getLeft()), computeHeight(p->getRight())) + 1);
}

template <typename T>
void printAVL(AVL<T> *tree)
{
  std::cout << "pre-order" << std::endl;
  tree->preorder(tree->getRoot());
  // std::cout << tree->getRoot()->getElm() << "hi";
  std::cout << std::endl;
  std::cout << "in-order" << std::endl;
  tree->inorder(tree->getRoot());
  // std::cout << tree->getRoot()->getElm() << "hi";
  std::cout << std::endl;
}

template <typename T>
void deleteAVLTree(BSTNode<T> *p)
{
  if (p == nullptr)
  {
    return;
  }
  else
  {
    deleteAVLTree(p->getLeft());
    deleteAVLTree(p->getRight());
  }
  delete p;
}

template <typename T>
void deleteAVLTree(AVL<T> *tree)
{
  deleteAVLTree(tree->getRoot());
  tree->setRoot(nullptr);
}

template <typename T>
AVL<T> *buildAVLTree(const std::string &fileName)
{
  AVL<T> *avl = new AVL<T>();
  std::ifstream file(fileName);
  if (!file.is_open())
  {
    std::cout << "File name is not correct" << std::endl;
    return nullptr;
  }
  else
  {

    int numberOfDataPoints;
    file >> numberOfDataPoints;

    for (int i = 0; i < numberOfDataPoints; i++)
    {
      T data;
      file >> data;
      avl->insert(data);
    }
  }
  file.close();
  return avl;
}

template <typename T>
void insertNodeAVL(AVL<T> *tree, int element)
{
  tree->insert(element);
  BSTNode<T> *currentNode = tree->getRoot();
  while (currentNode != nullptr)
  {
    int heightOfLeft = tree->computeHeight(currentNode->getLeft());
    int heightOfRight = tree->computeHeight(currentNode->getRight());
    int currentNodeHeight = std::max(heightOfLeft, heightOfRight) + 1;
    currentNode->setHeight(currentNodeHeight);

    int balanceFactor = heightOfLeft - heightOfRight;

    if (balanceFactor < -1 || balanceFactor > 1)
    {
      if (element < currentNode->getElm())
      {
        if (element < currentNode->getLeft()->getElm())
        {
          currentNode = tree->rotateRight(currentNode);
        }
        else
        {
          currentNode = tree->rotateLeftRight(currentNode);
        }
      }
      else
      {
        if (element > currentNode->getRight()->getElm())
        {
          currentNode = tree->rotateLeft(currentNode);
        }
        else
        {
          currentNode = tree->rotateRightLeft(currentNode);
        }
      }
      heightOfLeft = tree->computeHeight(currentNode->getLeft());
      heightOfRight = tree->computeHeight(currentNode->getRight());
      currentNodeHeight = std::max(heightOfLeft, heightOfRight) + 1;
      currentNode->setHeight(currentNodeHeight);
    }
    if (element < currentNode->getElm())
    {
      currentNode = currentNode->getLeft();
    }
    else
    {
      currentNode = currentNode->getRight();
    }
  }
}

template <typename T>
void deleteNodeAVL(AVL<T> *tree, int element)
{

  BSTNode<T> *parent = nullptr;
  BSTNode<T> *currentNode = tree->getRoot();

  while (currentNode != nullptr && currentNode->getElm() != element)
  {
    parent = currentNode;

    if (element < currentNode->getElm())
    {
      currentNode = currentNode->getLeft();
    }
    else
    {
      currentNode = currentNode->getRight();
    }
  }
  if (currentNode == nullptr)
  {
    return;
  }
  else
  {
    tree->deleteByCopying(currentNode);
  }

  parent = nullptr;
  currentNode = tree->getRoot();
  while (currentNode != nullptr && currentNode->getElm() != element)
  {
    parent = currentNode;
    if (element < currentNode->getElm())
    {
      currentNode = currentNode->getLeft();
    }
    else
    {
      currentNode = currentNode->getRight();
    }
  }
  while (parent != nullptr)
  {
    int heightOfLeft = tree->computeHeight(parent->getLeft());
    int heightOfRight = tree->computeHeight(parent->getRight());
    int parentHeight = std::max(heightOfLeft, heightOfRight) + 1;
    parent->setHeight(parentHeight);
    int balanceFactor = heightOfLeft - heightOfRight;

    if (balanceFactor < -1 || balanceFactor > 1)
    {
      if (balanceFactor > 1)
      {
        if (tree->computeHeight(parent->getLeft()->getLeft()) >= tree->computeHeight(parent->getLeft()->getRight()))
        {
          parent = tree->rotateRight(parent);
        }
        else
        {
          parent->setLeft(tree->rotateLeft(parent->getLeft()));
          parent = tree->rotateRight(parent);
        }
      }
      else
      {
        if (tree->computeHeight(parent->getRight()->getRight()) >= tree->computeHeight(parent->getRight()->getLeft()))
        {
          parent = tree->rotateLeft(parent);
        }
        else
        {
          parent->setRight(tree->rotateRight(parent->getRight()));
          parent = tree->rotateLeft(parent);
        }
      }
      int heightOfLeft = tree->computeHeight(parent->getLeft());
      int heightOfRight = tree->computeHeight(parent->getRight());
      int parentHeight = std::max(heightOfLeft, heightOfRight) + 1;
      parent->setHeight(parentHeight);
    }
    parent = parent->getParent();
  }
}
template <typename T>
int AVL<T>::height() const
{
  return computeHeight(this->getRoot());
}

#endif