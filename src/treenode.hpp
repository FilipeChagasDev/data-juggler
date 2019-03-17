#ifndef TREENODE_HPP
#define TREENODE_HPP

#include "exception.hpp"

namespace DataJuggler {

class BinaryTreeNode
{
    public:
        enum Branch {left_branch, right_branch, none_branch};

    protected:
        Branch onBranchOfHigher;
        BinaryTreeNode *higher;
        BinaryTreeNode *left;
        BinaryTreeNode *right;

    public:
        BinaryTreeNode();
        virtual ~BinaryTreeNode();

        void insertLeft(BinaryTreeNode *to_insert);
        void insertRight(BinaryTreeNode *to_insert);
        Branch getBranchOfHigher();
        BinaryTreeNode *getHigher();
        BinaryTreeNode *getLeft();
        BinaryTreeNode *getRight();
        bool isRoot();
        bool isLeaf();
        bool isOnly();
        virtual void deleteSubtree();
        static void recursiveDeleteSubtree(BinaryTreeNode *node);
};

} //end of namespace

#endif // TREENODE_HPP
