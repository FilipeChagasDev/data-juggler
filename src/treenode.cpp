#include "treenode.hpp"
namespace DataJuggler {

// --------------------- constructors ------------------------

BinaryTreeNode::BinaryTreeNode()
{
    this->onBranchOfHigher = BinaryTreeNode::Branch::none_branch;
    this->higher = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}

BinaryTreeNode::~BinaryTreeNode()
{
}

// -------------------- getters -----------------------

BinaryTreeNode* BinaryTreeNode::getHigher()
{
    return this->higher;
}

BinaryTreeNode* BinaryTreeNode::getLeft()
{
    return this->left;
}

BinaryTreeNode* BinaryTreeNode::getRight()
{
    return this->right;
}

BinaryTreeNode::Branch BinaryTreeNode::getBranchOfHigher()
{
    return this->onBranchOfHigher;
}

// -------------------- inserters -----------------------

void BinaryTreeNode::insertLeft(BinaryTreeNode *to_insert)
{
    //check for errors
    if(to_insert == nullptr)
    {
        throw new InvalidArgsEx("BinaryTreeNode::insertLeft", "BinaryTreeNode *to_insert");
    }

    //insert...
    to_insert->higher = this;
    to_insert->onBranchOfHigher = left_branch;
    this->left = to_insert;

}

void BinaryTreeNode::insertRight(BinaryTreeNode *to_insert)
{
    //check for errors
    if(to_insert == nullptr)
    {
        throw new InvalidArgsEx("BinaryTreeNode::insertLeft", "BinaryTreeNode *to_insert");
    }

    //insert...
    to_insert->higher = this;
    to_insert->onBranchOfHigher = right_branch;
    this->right = to_insert;
}

// ---------------- deleters ---------------------

void BinaryTreeNode::recursiveDeleteSubtree(BinaryTreeNode *node)
{
    if(node == nullptr) return;

    recursiveDeleteSubtree(node->left);
    recursiveDeleteSubtree(node->right);

    if(node->isLeaf())
    {
        if(node->onBranchOfHigher == BinaryTreeNode::Branch::right_branch)
        {
            node->higher->right = nullptr;
        }
        else if(node->onBranchOfHigher == BinaryTreeNode::Branch::left_branch)
        {
            node->higher->left = nullptr;
        }

        delete node;
    }
}

void BinaryTreeNode::deleteSubtree()
{
    BinaryTreeNode::recursiveDeleteSubtree(this);
}

// ------------------------ booleans -------------------------

bool BinaryTreeNode::isRoot()
{
    return (this->higher == nullptr);
}

bool BinaryTreeNode::isLeaf()
{
    return (this->left == nullptr && this->right == nullptr);
}

bool BinaryTreeNode::isOnly()
{
    return (this->isLeaf() && this->isRoot());
}

} //end of namespace