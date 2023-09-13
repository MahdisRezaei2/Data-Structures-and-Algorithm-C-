#ifndef BST_H
#define BST_H
#include <iostream>
#include "math.h"

// Class Node
template <typename T>
class BSTNode
{
public:
	BSTNode()
	{
		left = right = nullptr;
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
	

private:
	T elm;
	BSTNode<T> *left, *right;
};

// class BST
template <typename T>
class BST
{

public:
	BSTNode<T> *getRoot() const;
	T *search(BSTNode<T> *p, const T &elm) const;
	void visit(BSTNode<T> *p);
	void inorder(BSTNode<T> *p);
	void preorder(BSTNode<T> *p);
	void insert(const T &el);
	void deleteByCopying(BSTNode<T> *&node);

private:
	int height;
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
		if (elm == p->elm)
		{
			return &(p->elm);
		}
		else if (elm <= p->elm)
			p = p->left;
		else
			p = p->right;
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
		preorder(p->left);
		preorder(p->right);
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
	if (node->right == nullptr)
		node = node->left;
	else if (node->left == nullptr)
		node = node->right;
	else
	{
		tmp = node->left;
		previous = node;
		while (tmp->right != nullptr)
		{
			previous = tmp;
			tmp = tmp->right;
		}
		node->elm = tmp->elm;
		if (previous == node)
			previous->left = tmp->left;
		else
			previous->right = tmp->left;
	}
	delete tmp;
}

#endif