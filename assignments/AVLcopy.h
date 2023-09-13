
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