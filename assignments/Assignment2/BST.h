#ifndef BST_H
#define BST_H
#include <iostream>
#include "math.h"

// Class Node
template <typename T>
class BSTNode
{
public: 
   // int height;
	BSTNode()
	{
		left = right =parent= nullptr;
		height=0;
	}
	BSTNode(const T &e, BSTNode<T> *l = nullptr, BSTNode<T> *r = nullptr)
	{
		elm = e;
		left = l;
		right = r;
	}
	T getElm() const
	{
		return elm;
	}
	void setElm(T el){
		elm=el;
	}
	BSTNode<T> *getLeft() const
	{
		return left;
	}
	BSTNode<T> *getRight() const
	{
		return right;
	}
	void setLeft(BSTNode<T> *l)
	{
		left = l;
	}
	void setRight(BSTNode<T> *r)
	{
		right = r;
	}
	int getHeight()const{
		return height;
	}
	void setHeight(int h){
		height=h;
	}
    BSTNode<T> *getParent()const{
		return parent;
	}
	void setParent(BSTNode<T>*p){
		parent= p;
	}
private:
	T elm;
	BSTNode<T> *left, *right,*parent;
	int height;
};

// class BST
template <typename T>
class BST
{

public:
	BSTNode<T> *getRoot() const;
	T *search(BSTNode	<T> *p, const T &elm) const;
	void visit(BSTNode<T> *p);
	void inorder(BSTNode<T> *p);
	void preorder(BSTNode<T> *p);
	void insert(const T &el);
	void deleteByCopying(BSTNode<T> *&node);

private:
	//int height;
	BSTNode<T> *root;
};

// getRoot function implementation
template <typename T>
BSTNode<T> *BST<T>::getRoot() const
{
	return root;
}

// Search function implementation
template <typename T>
T *BST<T>::search(BSTNode<T> *p, const T &elm) const
{

	while (p != nullptr)
	{
		if (elm == p->getElm())
		{
			return (p->getElm());
		}
		else if (elm <= p->getElm())
			p = p->getLeft();
		else
			p = p->getRight();
	}
	return nullptr;
}

// visit function implementation
template <typename T>
void BST<T>::visit(BSTNode<T> *p)
{
	std::cout << p->getElm() << " ";
}
template <typename T>
void BST<T>::inorder(BSTNode<T> *p)
{
	if (p != nullptr)
	{
		inorder(p->getLeft());
		visit(p);
		inorder(p->getRight());
	}
}

//preorder function implementation
template <typename T>
void BST<T>::preorder(BSTNode<T> *p)
{   
	if (p != nullptr)
	{
		visit(p);
		preorder(p->getLeft());
		preorder(p->getRight());
		
	}
}

//insert function implementation
template <typename T>
void BST<T>::insert(const T &el)
{
	BSTNode<T> *p = root, *prev = 0;
	BSTNode<T> *newNode;
	while (p != nullptr)
	{
		prev = p;
		if (el <= p->getElm())
			p = p->getLeft();
		else
			p = p->getRight();
	}
	newNode = new BSTNode<T>(el);
	if (root == nullptr)
		root = new BSTNode<T>(el);
	else if (el < prev->getElm())
		prev->setLeft(newNode);
	else
		prev->setRight(newNode);
}

//deleteByCopying function implementation
template <typename T>
void BST<T>::deleteByCopying(BSTNode<T> *&node)
{
	BSTNode<T> *previous, *tmp = node;
	if (node->getRight() == nullptr)
		node = node->getLeft();
	else if (node->getLeft()== nullptr)
		node = node->getRight();
	else
	{
		tmp = node->getLeft();
		previous = node;
		while (tmp->getRight() != nullptr)
		{
			previous = tmp;
			tmp = tmp->getRight();
		}
		node->setElm( tmp->getElm());
		if (previous == node)
			previous->setLeft(tmp->getLeft());
		else
			previous->setRight(tmp->getLeft());
	}
	delete tmp;
}

#endif