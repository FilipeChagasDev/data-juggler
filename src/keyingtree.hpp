#ifndef KEYINGTREE_HPP
#define KEYINGTREE_HPP

#include "treenode.hpp"
#include "exception.hpp"
#include "lambda.hpp"

namespace DataJuggler {

/** Class that is instantiated and throwed when the program try to insert a repeated key in a KeyingTree. */
class KeyAlreadyInsertedEx : public Exception
{
    public:
        long long key;
        KeyAlreadyInsertedEx(long long key);
        static const unsigned long defaultCode = 12504;
};

/** Class that is instantied and throwed when the program try to find a non inserted key in a KeyingTree */
class KeyNotFoundEx : public Exception
{
    public:
        long long key;
        KeyNotFoundEx(long long key);
        static const unsigned long defaultCode = 5327;
};

/** Class that is instantied and throwed when the specified tree node does not belong to the keying tree */
class NodeNotOwnedEx : public Exception
{
    public:
        NodeNotOwnedEx();
        static const unsigned long defultCode = 6154;
};

// -------- Exceptions implementation ----------------

KeyAlreadyInsertedEx::KeyAlreadyInsertedEx(long long key)
    :Exception (KeyAlreadyInsertedEx::defaultCode, "Key Already Inserted Exception",
                "Key is already in the tree")
{
    this->key = key;
}

KeyNotFoundEx::KeyNotFoundEx(long long key)
    :Exception (KeyNotFoundEx::defaultCode, "Key not found exception", "Cannot find the key in the keying tree")
{
    this->key = key;
}

NodeNotOwnedEx::NodeNotOwnedEx()
    :Exception (NodeNotOwnedEx::defultCode, "Node not owned", "The specified tree node does not belong to the keying tree")
{
}

// -------- KeyingTreeNode declaration -----
/** Node from a keying tree */
template<typename keytype, typename datatype>
class KeyingTreeNode : public BinaryTreeNode
{
    public:
        KeyingTreeNode(keytype key, datatype data);
        datatype data;
        keytype key;
        void forEachNode(function<bool(KeyingTreeNode<keytype, datatype>*)> callback);
};

// -------- KeyingTreeNode implementation -----
template<typename keytype, typename datatype>
KeyingTreeNode<keytype, datatype>::KeyingTreeNode(keytype key, datatype data)
   : BinaryTreeNode()
{
    this->key = key;
    this->data = data;
}

template<typename keytype, typename datatype>
void KeyingTreeNode<keytype, datatype>::forEachNode(function<bool(KeyingTreeNode<keytype, datatype>*)> callback)
{
    if(this->getLeft() != nullptr)
        static_cast<KeyingTreeNode<keytype, datatype>*>(this->getLeft())->forEachNode(callback);

    if(callback(this) == true) return; //break

    if(this->getRight() != nullptr)
        static_cast<KeyingTreeNode<keytype, datatype>*>(this->getRight())->forEachNode(callback);
}

// -------- KeyingTree declaration --------

/** This class is the header to a binary keying tree. In this binary tree, the Nodes are quickly sought with binary search for keys.*/
template<typename keytype, typename datatype>
class KeyingTree
{
    protected:
        KeyingTreeNode<keytype, datatype> *root;

    public:
        /** Constructor */
        KeyingTree();

        /** Destructor */
        ~KeyingTree();

        /**This method returns the root node of the tree*/
        KeyingTreeNode<keytype, datatype> *getRoot();

        /**This method returns the data from a node found in the tree by the corresponding key.
        An KeyNotFoundEx will be throwed whether the find method does not find this key.*/
        datatype find(keytype key);

        /**This method returns the pointer to a node found in the tree by the corresponding key.
        if the findNode method does not find this key, a nullptr will be returned.*/
        KeyingTreeNode<keytype, datatype> *findNode(keytype key);

        /**This method creates a node with the data and the key specified in the arguments and
        inserts in the tree. If there is already another node with this same key in the tree, an
        KeyAlreadyInsertedEx will be thrown.*/
        void insert(keytype key, datatype data);

        /**This method inserts the node specified in the arguments in the tree.
        If there is already another node with the same key in the tree, an
        KeyAlreadyInsertedEx will be thrown.
        This method is not safe, prefer to use the insert method whenever possible.*/
        void insertNode(KeyingTreeNode<keytype, datatype> *node);

        /**finds the node with the key specified in the argument and removes
        it from the tree. The sub-trees of this node will be re-inserted in the tree.
        If there is no node with this key in the tree, a KeyNotFoundEx will be throw.*/
        void remove(keytype key);

        /** Checks if the argument node belongs to the tree and, if so,
        removes it and re-inserts its subtree. If the argument node does not belong to the tree,
        a NodeNotOwnedEx is throw. */
        void removeNode(KeyingTreeNode<keytype, datatype> *node);

        /** Checks if there is a node with the argument key in the tree. If yes, returns true.*/
        bool belongingKey(keytype key);

        /** Checks if there is a node with the argument data in the tree. If yes, returns true.*/
        bool belongingData(datatype data);

        /** Check if the node of the argument belongs to the tree. If yes, returns true.*/
        bool belongingNode(KeyingTreeNode<keytype, datatype> *node);

        /** This is a functional forEach. This method takes as argument a function
        (or a lambda) that returns a bool and receives a KeyingTreeNode. The tree will
        be traversed symmetrically, from the smallest to the largest key, and for each
        node traversed, a call to the function of the argument will be performed, passing its node as argument to it.
        If the argument function returns true, the forEach job is stopped, and the arguments function calls will cease.
        If the function returns false, the forEach job continues.*/
        void forEachNode(function<bool(KeyingTreeNode<keytype, datatype>*)> callback);

        /** This is a functional forEach. This method takes as argument a function
        (or a lambda) that returns a bool and receives a key and a data from a node. The tree will
        be traversed symmetrically, from the smallest to the largest key, and for each
        node traversed, a call to the function of the argument will be performed, passing the key
        and the data from this node as argument to it.
        If the argument function returns true, the forEach job is stopped, and the arguments function calls will cease.
        If the function returns false, the forEach job continues.*/
        void forEach(function<bool(keytype,datatype)> callback);
};

// ----------- KeyingTree implementation ---------

//constructor
template<typename keytype, typename datatype>
KeyingTree<keytype, datatype>::KeyingTree()
{
    this->root = nullptr;
}

//destructor
template<typename keytype, typename datatype>
KeyingTree<keytype, datatype>::~KeyingTree()
{
   if(this->root != nullptr) this->root->deleteSubtree();
}

template<typename keytype, typename datatype>
KeyingTreeNode<keytype, datatype> *KeyingTree<keytype, datatype>::getRoot()
{
    return this->root;
}

template<typename keytype, typename datatype>
datatype KeyingTree<keytype, datatype>::find(keytype key)
{
    KeyingTreeNode<keytype, datatype> *current_node = this->root;
    while (current_node != nullptr)
    {
        if(current_node->key == key) return current_node->data;
        else if(current_node->key > key) current_node = static_cast<KeyingTreeNode<keytype, datatype>*>(current_node->getLeft());
        else if(current_node->key < key) current_node = static_cast<KeyingTreeNode<keytype, datatype>*>(current_node->getRight());
    }

    throw new KeyNotFoundEx(key);
}

template<typename keytype, typename datatype>
KeyingTreeNode<keytype, datatype>* KeyingTree<keytype, datatype>::findNode(keytype key)
{
    KeyingTreeNode<keytype, datatype> *iterator = this->root;
    while (iterator != nullptr)
    {
        if(iterator->key == key) return iterator;
        else if(iterator->key > key) iterator = static_cast<KeyingTreeNode<keytype, datatype>*>(iterator->getLeft());
        else if(iterator->key < key) iterator = static_cast<KeyingTreeNode<keytype, datatype>*>(iterator->getRight());
    }

    return nullptr;
}

template<typename keytype, typename datatype>
void KeyingTree<keytype, datatype>::insert(keytype key, datatype data)
{
    KeyingTreeNode<keytype, datatype> *new_node = new KeyingTreeNode<keytype, datatype>(key,data);

    if(this->root == nullptr) //when tree is empty
    {
        this->root = new_node;
    }
    else
    {
        KeyingTreeNode<keytype, datatype> *prev_iterator = this->root;
        KeyingTreeNode<keytype, datatype> *iterator = this->root;
        while (iterator != nullptr)
        {
            prev_iterator = iterator;
            if(iterator->key == key) throw KeyAlreadyInsertedEx(key);
            else if(iterator->key > key) iterator = static_cast<KeyingTreeNode<keytype, datatype>*>(iterator->getLeft());
            else if(iterator->key < key) iterator = static_cast<KeyingTreeNode<keytype, datatype>*>(iterator->getRight());
        }

        if(prev_iterator->key > key) prev_iterator->insertLeft(new_node);
        else if(prev_iterator->key < key) prev_iterator->insertRight(new_node);
    }
}

template<typename keytype, typename datatype>
void KeyingTree<keytype, datatype>::insertNode(KeyingTreeNode<keytype, datatype> *node)
{
    if(node == nullptr) throw new InvalidArgsEx("KeyingTree::insertNode", "*node is null");

    if(this->root == nullptr) //when tree is empty
    {
        this->root = node;
    }
    else
    {
        KeyingTreeNode<keytype, datatype> *prev_iterator = this->root;
        KeyingTreeNode<keytype, datatype> *iterator = this->root;
        while (iterator != nullptr)
        {
            prev_iterator = iterator;
            if(iterator->key == node->key) throw KeyAlreadyInsertedEx(node->key);
            else if(iterator->key > node->key) iterator = static_cast<KeyingTreeNode<keytype, datatype>*>(iterator->getLeft());
            else if(iterator->key < node->key) iterator = static_cast<KeyingTreeNode<keytype, datatype>*>(iterator->getRight());
        }

        if(prev_iterator->key > node->key) prev_iterator->insertLeft(node);
        else if(prev_iterator->key < node->key) prev_iterator->insertRight(node);
    }
}

template<typename keytype, typename datatype>
void KeyingTree<keytype, datatype>::remove(keytype key)
{
    KeyingTreeNode<keytype, datatype> *to_remove = this->findNode(key);
    if(to_remove == nullptr) throw new KeyNotFoundEx(key);
    KeyingTreeNode<keytype, datatype> *left = static_cast<KeyingTreeNode<keytype, datatype>*>(to_remove->getLeft());
    KeyingTreeNode<keytype, datatype> *right = static_cast<KeyingTreeNode<keytype, datatype>*>(to_remove->getRight());

    if(to_remove == this->root) this->root = nullptr;
    delete to_remove;

    if(left != nullptr) this->insertNode(left);
    if(right != nullptr) this->insertNode(right);
}

template<typename keytype, typename datatype>
void KeyingTree<keytype, datatype>::removeNode(KeyingTreeNode<keytype, datatype> *node)
{
    if(node == nullptr) throw new InvalidArgsEx("KeyingTree::removeNode", "*node is null");
    if(this->findNode(node->key) != node) throw new NodeNotOwnedEx();
    KeyingTreeNode<keytype, datatype> *left = static_cast<KeyingTreeNode<keytype, datatype>*>(node->getLeft());
    KeyingTreeNode<keytype, datatype> *right = static_cast<KeyingTreeNode<keytype, datatype>*>(node->getRight());

    if(node == this->root) this->root = nullptr;
    delete node;

    if(left != nullptr) this->insertNode(left);
    if(right != nullptr) this->insertNode(right);
}

template<typename keytype, typename datatype>
bool KeyingTree<keytype, datatype>::belongingKey(keytype key)
{
    KeyingTreeNode<keytype, datatype> *iterator = this->root;
    while (iterator != nullptr)
    {
        if(iterator->key == key) return true;
        else if(iterator->key > key) iterator = static_cast<KeyingTreeNode<keytype, datatype>*>(iterator->getLeft());
        else if(iterator->key < key) iterator = static_cast<KeyingTreeNode<keytype, datatype>*>(iterator->getRight());
    }
    return false;
}

template<typename keytype, typename datatype>
bool KeyingTree<keytype, datatype>::belongingData(datatype data)
{
    bool found = false;
    if(this->root != nullptr)
        this->root->forEachNode([&](KeyingTreeNode<keytype, datatype>* node)->bool
        {
            if(data == node->data)
            {
                found = true;
                return true; //break forEach
            }
        });

    return found;
}

template<typename keytype, typename datatype>
bool KeyingTree<keytype, datatype>::belongingNode(KeyingTreeNode<keytype, datatype> *node)
{
    bool found = false;
    if(this->root != nullptr)
        this->root->forEachNode([&](KeyingTreeNode<keytype, datatype>* lambda_node)->bool
        {
            if(node == lambda_node)
            {
                found = true;
                return true; //break forEach
            }
            return false;
        });

    return found;
}

template<typename keytype, typename datatype>
void KeyingTree<keytype, datatype>::forEachNode(function<bool(KeyingTreeNode<keytype, datatype>*)> callback)
{
    this->root->forEachNode(callback);
}

template<typename keytype, typename datatype>
void KeyingTree<keytype, datatype>::forEach(function<bool(keytype, datatype)> callback)
{
    this->root->forEachNode([&](KeyingTreeNode<keytype, datatype> *node)->bool
    {
        return callback(node->key, node->data);
    });
}



}//end of namespace
#endif // KEYINGTREE_HPP
