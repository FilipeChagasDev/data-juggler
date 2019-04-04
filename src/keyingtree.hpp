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

// -------- KeyAlreadyInserted implementation ----------------

KeyAlreadyInsertedEx::KeyAlreadyInsertedEx(unsigned long key)
    :Exception (KeyAlreadyInsertedEx::defaultCode, "Key Already Inserted Exception",
                "Key is already in the tree")
{
    this->key = key;
}

// -------- KeyingTree declaration --------

/** This class is the header to a binary keying tree. In this binary tree, the Nodes are quickly sought with binary search for keys.*/
template<typename datatype>
class KeyingTree
{
    public:
        /** Node from a keying tree */
        class Node : public BinaryTreeNode
        {
            public:
                datatype data;
                unsigned long key;
                KeyingTree *header;
        };

    protected:
        Node *root;

    public:
        Node *getRoot(); //TODO
        datatype find(unsigned long key); //TODO
        Node *findNode(unsigned long key); //TODO
        void insert(datatype data); //TODO
        void insertData(Node *node); //TODO
        void remove(unsigned long key); //TODO
        void removeNode(Node *node); //TODO
};

}//end of namespace
#endif // KEYINGTREE_HPP
