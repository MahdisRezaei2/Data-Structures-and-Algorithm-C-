#ifndef AVL_H
#define AVL_H
#include <iostream>
#include "BST.h"
// *&node     *node
template <typename T>

class AVL : public BST<T>
{

public:
  void insert(const T &elm);
  void deleteByCopying(BSTNode<T> *&node);
  void remove(const T &elm);
  bool checkBalance() const;

private:
  int computeHeight(BSTNode<T> *p) const;
  void updateHeight(BSTNode<T> *p);
  BSTNode<T> *rotateRight(BSTNode<T> *p);
  BSTNode<T> *rotateLeft(BSTNode<T> *p);
  BSTNode<T> *rotateLeftRight(BSTNode<T> *p);
  BSTNode<T> *rotateRightLeft(BSTNode<T> *p);
  BSTNode<T> *balance(BSTNode<T> *p);

  BSTNode<T> *insert(const T &elm, BSTNode<T> *p);
  bool checkBalance(BSTNode<T> *p) const;

  BSTNode<T> *root;
};

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
  std::cout << "hi insert";
    if (p == nullptr)
    std::cout << "hi from insert 2";
  return new BSTNode<T>(elm);
  if (elm < p->getElm()){
    std::cout << "hi from left ";
    p->setLeft(insert(elm, p->getLeft()));
  }
  else
    p->setRight(insert(elm, p->getRight()));

  // updateHeight(p); // to update the hight of each node during recursive insertion, so the hight information will be accurate when want to balance the tree
  std::cout << "hi from insert 3";

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

// remove implementation
template <typename T>
void AVL<T>::remove(const T &elm)
{

  /*search for the node containing elm
   * if the node is not found, the search function will return nullptr, which makes the if condition false so the function won't remove anything
   * this is the current instance of the AVL class
   */
  BSTNode<T> *node = this->search(this->getRoot(), elm);

  // if the node is not a nullptr, means the node is found, we delete it
  if (node != nullptr)
  {
    deleteByCopying(node);
  }
  // Check balance
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
  else if(computeHeight(p->getRight()) - computeHeight(p->getLeft()) > 1){
    if (computeHeight(p->getRight()->getRight()) >= computeHeight(p->getRight()->getLeft()))
    p = rotateLeft(p);
    else{
      p->setRight(rotateRight(p->getRight()));
      p= rotateLeft(p);
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
#endif