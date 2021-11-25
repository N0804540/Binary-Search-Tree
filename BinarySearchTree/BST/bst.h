#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>

class BST
{
    public:
        using KeyType = int;
        using ItemType = std::string;

        ItemType* lookup(KeyType);
        void insert(KeyType, ItemType);
        void remove(KeyType);
        void displayEntries();

        BST() = default;

    private:
        struct Node;
        Node* root = leaf();
        static Node* leaf();
        static bool isLeaf(Node*);

        ItemType* lookupRec(KeyType, Node*);
        void insertRec(KeyType, ItemType, Node* &);
        void displayEntriesRec(Node*);
        void removeRec(KeyType, Node* &);
        Node* detachMinimumNode(Node* &);
};

#endif