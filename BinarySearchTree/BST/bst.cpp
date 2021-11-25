#include "bst.h"

struct BST::Node
{
    KeyType key;
    ItemType item;
    Node* leftChild;
    Node* rightChild;
    Node(KeyType, ItemType);
};

BST::Node::Node(BST::KeyType key, BST::ItemType item)
{
    this->key = key;
    this->item = item;
    this->leftChild = BST::leaf();
    this->rightChild = BST::leaf();
}

BST::ItemType* BST::lookup(KeyType soughtKey)
{
    return lookupRec(soughtKey, this->root);
}

BST::ItemType* BST::lookupRec(KeyType soughtKey, Node* currentNode)
{
    if(!isLeaf(currentNode))
    {
        int x = soughtKey - currentNode->key;
        if(x > 0)
        {
            return lookupRec(soughtKey, currentNode->rightChild);
        }
        else if(x < 0)
        {
            return lookupRec(soughtKey, currentNode->leftChild);
        }
        else
        {
            return &currentNode->item;
        }
    }
    return nullptr;
}

void BST::insert(BST::KeyType newKey, BST::ItemType newItem)
{
    insertRec(newKey, newItem, this->root);
}

void BST::insertRec(BST::KeyType newKey, BST::ItemType newItem, BST::Node* &currentNode)
{
    if(isLeaf(currentNode))
    {
        Node* newNode = new Node(newKey, newItem);
        currentNode = newNode;
    }
    else
    {
        if(newKey > currentNode->key)
        {
            insertRec(newKey, newItem, currentNode->rightChild);
        }
        else if(newKey < currentNode->key)
        {
            insertRec(newKey, newItem, currentNode->leftChild);
        }
        else
        {
            currentNode->item = newItem;
        }
    }
}

void BST::displayEntries()
{
    if(isLeaf(this->root))
    {
        std::cout << "This tree is empty" << std::endl;
    }
    else
    {
        displayEntriesRec(this->root);
    }
}

void BST::displayEntriesRec(Node* currentNode)
{
    if(!isLeaf(currentNode->leftChild))
    {
        displayEntriesRec(currentNode->leftChild);
    }
    std::cout << "(" << currentNode->key << ", " << currentNode->item << ")" << std::endl;
    if(!isLeaf(currentNode->rightChild))
    {
        displayEntriesRec(currentNode->rightChild);
    }
}

void BST::remove(BST::KeyType removeNode)
{
    removeRec(removeNode, this->root);
}

void BST::removeRec(BST::KeyType removeNode, Node* &currentNode)
{
    if(isLeaf(currentNode))
    {
        return;
    }
    else
    {
        if(removeNode == currentNode->key)
        {
            if(isLeaf(currentNode->rightChild) && isLeaf(currentNode->leftChild))
            {
                currentNode = leaf();            
            }
            else if(!isLeaf(currentNode->rightChild) && isLeaf(currentNode->leftChild))
            {
                currentNode = currentNode->rightChild;
            }
            else if(isLeaf(currentNode->rightChild) && !isLeaf(currentNode->leftChild))
            {
                currentNode = currentNode->leftChild;
            }
            else
            {
                Node* minimumNode = detachMinimumNode(currentNode->rightChild);
                currentNode->key = minimumNode->key;
                currentNode->item = minimumNode->item;
            }
        }
        else if(removeNode > currentNode->key)
        {
            removeRec(removeNode, currentNode->rightChild);
        }
        else if(removeNode < currentNode->key)
        {
            removeRec(removeNode, currentNode->leftChild);
        }
    }
}

BST::Node* BST::detachMinimumNode(Node* &currentNode)
{
    if(isLeaf(currentNode->leftChild))
    {
        Node* minimumNode = new Node(currentNode->key, currentNode->item);
        currentNode = leaf();
        return minimumNode;
    }
    else
    {
        return detachMinimumNode(currentNode->leftChild);
    }
}

BST::Node* BST::leaf()
{
    return nullptr;
}

bool BST::isLeaf(BST::Node* n)
{
    return n == nullptr;
}