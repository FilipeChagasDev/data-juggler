#ifndef TREENODE_HPP
#define TREENODE_HPP

#include "exception.hpp"
#include "lambda.hpp"

namespace DataJuggler {

/** This class represents the node of a binary tree, with pointer to left branch, direct branch, and upper node.
This class is very basic and should not be instantiated directly. Subclasses of this can be used to enter information
(such as numbers, keys, objects) on the node and perform operations such as rotation and sorting on the tree.   */
class BinaryTreeNode
{
    public:
        enum Branch {left_branch, right_branch, none_branch};

    protected:
        Branch onBranchOfUpper;
        BinaryTreeNode *upper;
        BinaryTreeNode *left;
        BinaryTreeNode *right;
        static long recursiveGetDistanceDown(BinaryTreeNode *from, BinaryTreeNode *to, long counter = 1);

    public:
        BinaryTreeNode();

        /** this destructor assign nullptr to all references to this BinaryTreeNode in the supertree in which
        it is inserted. Use very carefully, as the rest of the subtree is not deleted, maying cause a memory leakage.
        To delete the entire subtree, use the deleteSubtree function of the same class. */
        virtual ~BinaryTreeNode();

        /** This function recursively traverses all BinaryTreeNodes of the tree in preorder (left to right)
        from this BinaryTreeNode (from which this function was invoked). For each node picked on the tree, the
        callback function is called and a pointer to node is passed as an argument.   */
        void preOrder(function<void(BinaryTreeNode*)> callback);

        /** This function recursively traverses all BinaryTreeNodes of the tree in symmetric order
        from this BinaryTreeNode (from which this function was invoked). For each node picked on the
        tree, the callback function is called and a pointer to node is passed as an argument.   */
        void symmetricalOrder(function<void(BinaryTreeNode*)> callback);

        /** This function recursively traverses all BinaryTreeNodes of the tree in postorder
        from this BinaryTreeNode (from which this function was invoked). For each node picked on the
        tree, the callback function is called and a pointer to node is passed as an argument.   */
        void postOrder(function<void(BinaryTreeNode*)> callback);

        /** This function inserts a new BinaryTreeNode into the left branch of this BinaryTreeNode
        (from which this function was invoked). */
        void insertLeft(BinaryTreeNode *to_insert);

        /** This function inserts a new BinaryTreeNode into the right branch of this BinaryTreeNode
        (from which this function was invoked). */
        void insertRight(BinaryTreeNode *to_insert);

        /** This function returns an information of type BinaryTreeNode::Branch informing which of
        the two branches (left or right) of the upper BinaryTreeNode this BinaryTreeNode has been
        inserted.   */
        Branch getBranchOfUpper();

        /** This function gets a pointer to the upper BinaryTreeNode */
        BinaryTreeNode *getUpper();

        /** This function gets a pointer to the BinaryTreeNode on the left branch from this BinaryTreeNode*/
        BinaryTreeNode *getLeft();

        /** This function gets a pointer to the BinaryTreeNode on the right branch from this BinaryTreeNode*/
        BinaryTreeNode *getRight();

        /** This function gets the root of the supertree on which this BinaryTreeNode is inserted.
        If this BinaryTreeNode is the root of the tree itself, this function returns a pointer to it same.*/
        BinaryTreeNode *getSupertreeRoot();

        /** This function fetches the deepest BinaryTreeNode in the tree whose root is this.*/
        BinaryTreeNode *getDeeperSubtreeLeaf();

        /** This function obtains the distance of this BinaryTreeNode to another BinaryTreeNode of the same
        supertree (which must be passed as argument of this function). If the BinaryTreeNode passed as argument
        is not part of the same tree as this, the function returns -1.  */
        long getDistanceTo(BinaryTreeNode *reference);

        /** Returns true if this BinaryTreeNode is the root of a tree */
        bool isRoot();

        /** Returns true if this BinaryTreeNode is a leaf of the supertree in which it is inserted */
        bool isLeaf();

        /** Returns true if this BinaryTreeNode is a root and a leaf (does not have upper or lower BinaryTreeNodes). */
        bool isOnly();

        /** This function recursively deletes all BinaryTreeNodes from the subtree of which this is the root.
        IMPORTANT: After using this function, it is not necessary to use the destructor of this class to delete
        this BinaryTreeNode as this will cause a segmentation fault.*/
        virtual void deleteSubtree();
};

} //end of namespace

#endif // TREENODE_HPP



