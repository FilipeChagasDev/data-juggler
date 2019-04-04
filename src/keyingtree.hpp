#ifndef KEYINGTREE_HPP
#define KEYINGTREE_HPP

#include "treenode.hpp"
#include "exception.hpp"

namespace DataJuggler {

/** Class that is instantiated and throwed when the program try to insert a repeated key in a KeyingTree. */
class KeyAlreadyInsertedEx : Exception
{
    public:
        unsigned long key;
        KeyAlreadyInsertedEx(unsigned long key);
        static const unsigned long defaultCode = 12504;
};

/** Class that is instantied and throwed when the program try to find a non inserted key in a KeyingTree*/
class KeyNotFoundEx : Exception
{
    public:
        unsigned long key;
        KeyNotFoundEx(unsigned long key);
        static const unsigned long defaultCode = 5327;
};

// -------- Exceptions implementation ----------------

KeyAlreadyInsertedEx::KeyAlreadyInsertedEx(unsigned long key)
    :Exception (KeyAlreadyInsertedEx::defaultCode, "Key Already Inserted Exception",
                "Key is already in the tree")
{
    this->key = key;
}

KeyNotFoundEx::KeyNotFoundEx(unsigned long key)
    :Exception (KeyNotFoundEx::defaultCode, "Key not found exception", "Cannot find the key in the keying tree")
{
    this->key = key;
}

// -------- KeyingTreeNode declaration -----
/** Node from a keying tree */
template<typename datatype>
class KeyingTreeNode : public BinaryTreeNode
{
    public:
        KeyingTreeNode(unsigned long key, datatype data);
        datatype data;
        unsigned long key;
        KeyingTreeNode *root;
};

// -------- KeyingTreeNode implementation -----
template <typename datatype>
KeyingTreeNode<datatype>::KeyingTreeNode(unsigned long key, datatype data)
   : BinaryTreeNode()
{
    this->key = key;
    this->data = data;
}

// -------- KeyingTree declaration --------

/** This class is the header to a binary keying tree. In this binary tree, the Nodes are quickly sought with binary search for keys.*/
template<typename datatype>
class KeyingTree
{
    public:


    protected:
        KeyingTreeNode<datatype> *root;

    public:
        KeyingTreeNode<datatype> *getRoot();
        datatype find(unsigned long key); //TO TEST
        KeyingTreeNode<datatype> *findNode(unsigned long key); //TO TEST
        void insert(unsigned long key, datatype data); //TO TEST
        void insertNode(KeyingTreeNode<datatype> *node); //TO TEST
        void remove(unsigned long key); //TODO
        void removeNode(KeyingTreeNode<datatype> *node); //TODO
};

// ----------- KeyingTree implementation ---------

template<typename datatype>
KeyingTreeNode<datatype> *KeyingTree<datatype>::getRoot()
{
    return this->root;
}

template<typename datatype>
datatype KeyingTree<datatype>::find(unsigned long key)
{
    KeyingTreeNode<datatype> *current_node = this->root;
    while (current_node != nullptr)
    {
        if(current_node->key == key) return current_node->key;
        else if(current_node->key > key) current_node = current_node->getLeft();
        else if(current_node->key < key) current_node = current_node->getRight();
    }

    throw new KeyNotFoundEx(key);
}

template<typename datatype>
KeyingTreeNode<datatype>* KeyingTree<datatype>::findNode(unsigned long key)
{
    KeyingTreeNode<datatype> *iterator = this->root;
    while (iterator != nullptr)
    {
        if(iterator->key == key) return iterator;
        else if(iterator->key > key) iterator = iterator->getLeft();
        else if(iterator->key < key) iterator = iterator->getRight();
    }

    return nullptr;
}

template<typename datatype>
void KeyingTree<datatype>::insert(unsigned long key, datatype data)
{
    KeyingTreeNode<datatype> *new_node = new KeyingTreeNode<datatype>(key,data);
    KeyingTreeNode<datatype> *prev_iterator = this->root;
    KeyingTreeNode<datatype> *iterator = this->root;
    while (iterator != nullptr)
    {
        prev_iterator = iterator;
        if(iterator->key == key) throw KeyAlreadyInsertedEx(key);
        else if(iterator->key < key) iterator = iterator->getLeft();
        else if(iterator->key > key) iterator = iterator->getRight();
    }

    if(prev_iterator->key < key) prev_iterator->insertLeft(new_node);
    else if(prev_iterator->key > key) prev_iterator->insertRight(new_node);
}

template<typename datatype>
void KeyingTree<datatype>::insertNode(KeyingTreeNode<datatype> *node)
{
    if(node == nullptr) throw new InvalidArgsEx("KeyingTree::insertNode", "*node is null");

    KeyingTreeNode<datatype> *prev_iterator = this->root;
    KeyingTreeNode<datatype> *iterator = this->root;
    while (iterator != nullptr)
    {
        prev_iterator = iterator;
        if(iterator->key == node->key) throw KeyAlreadyInsertedEx(node->key);
        else if(iterator->key < node->key) iterator = iterator->getLeft();
        else if(iterator->key > node->key) iterator = iterator->getRight();
    }

    if(prev_iterator->key < node->key) prev_iterator->insertLeft(node);
    else if(prev_iterator->key > node->key) prev_iterator->insertRight(node);
}

}//end of namespace
#endif // KEYINGTREE_HPP
