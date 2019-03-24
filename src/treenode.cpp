#include "treenode.hpp"


namespace DataJuggler {

// --------------------- constructors ------------------------

BinaryTreeNode::BinaryTreeNode()
{
    this->onBranchOfUpper = BinaryTreeNode::Branch::none_branch;
    this->upper = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}

BinaryTreeNode::~BinaryTreeNode()
{   //set null all references to this object on the tree
    if(this->left != nullptr)
    {
        this->left->onBranchOfUpper = BinaryTreeNode::Branch::none_branch;
        this->left->upper = nullptr;
    }

    if(this->right != nullptr)
    {
        this->right->onBranchOfUpper = BinaryTreeNode::Branch::none_branch;
        this->right->upper = nullptr;
    }

    switch(this->onBranchOfUpper)
    {
        case BinaryTreeNode::Branch::left_branch:
        {
            this->upper->left = nullptr;
            break;
        }

        case BinaryTreeNode::Branch::right_branch:
        {
            this->upper->right = nullptr;
            break;
        }

        default:{}
    }
}

// ------------------- recursives ---------------------

void BinaryTreeNode::preOrder(function<void(BinaryTreeNode*)> callback)
{
    callback(this);
    if(this->left != nullptr) this->left->preOrder(callback);
    if(this->right != nullptr) this->right->preOrder(callback);
}

void BinaryTreeNode::symmetricalOrder(function<void(BinaryTreeNode*)> callback)
{
    if(this->left != nullptr) this->left->symmetricalOrder(callback);
    callback(this);
    if(this->right != nullptr) this->right->symmetricalOrder(callback);
}

void BinaryTreeNode::postOrder(function<void(BinaryTreeNode *)> callback)
{
    if(this->left != nullptr) this->left->postOrder(callback);
    if(this->right != nullptr) this->right->postOrder(callback);
    callback(this);
}

// -------------------- getters -----------------------

BinaryTreeNode* BinaryTreeNode::getUpper()
{
    return this->upper;
}

BinaryTreeNode* BinaryTreeNode::getLeft()
{
    return this->left;
}

BinaryTreeNode* BinaryTreeNode::getRight()
{
    return this->right;
}

BinaryTreeNode::Branch BinaryTreeNode::getBranchOfUpper()
{
    return this->onBranchOfUpper;
}

BinaryTreeNode* BinaryTreeNode::getSupertreeRoot()
{
    BinaryTreeNode *current = this;
    while(true)
    {
        if(current->getUpper() == nullptr)
        {
            return current;
        }
        else
        {
            current = current->getUpper();
        }
    }
}

long BinaryTreeNode::recursiveGetDistanceDown(BinaryTreeNode *from, BinaryTreeNode *to, long counter)
{
    if(from == nullptr) return -1;
    if(from == to) return counter;

    long l = recursiveGetDistanceDown(from->left, to, counter+1);
    long r = recursiveGetDistanceDown(from->right, to, counter+1);

    if(l == -1 && r == -1) return -1;
    else if(l != -1) return l;
    else if(r != -1) return r;
}

long BinaryTreeNode::getDistanceTo(BinaryTreeNode *reference)
{
    if(reference == nullptr)
    {
        throw new InvalidArgsEx("BinaryTreeNode::getDistanceTo", "*reference is null");
    }

    BinaryTreeNode *current = this;
    for(long i = 0; current != nullptr; i++)
    {
        if(current == reference)
        {
            return i;
        }
        current = current->upper;
    }

    return recursiveGetDistanceDown(this, reference, 0);
}

BinaryTreeNode* BinaryTreeNode::getDeeperSubtreeLeaf()
{
    BinaryTreeNode *deeper = this;
    long bigger_depth = 0;

    this->postOrder([&](BinaryTreeNode* node)
    {
        if(node->isLeaf() == false) return;

        long distance = node->getDistanceTo(this);
        if(distance > bigger_depth)
        {
            bigger_depth = distance;
            deeper = node;
        }
    });

    return deeper;
}


// -------------------- inserters -----------------------

void BinaryTreeNode::insertLeft(BinaryTreeNode *to_insert)
{
    //check for errors
    if(to_insert == nullptr)
    {
        throw new InvalidArgsEx("BinaryTreeNode::insertLeft", "*to_insert is null");
    }

    //insert...
    to_insert->upper = this;
    to_insert->onBranchOfUpper = left_branch;
    this->left = to_insert;

}

void BinaryTreeNode::insertRight(BinaryTreeNode *to_insert)
{
    //check for errors
    if(to_insert == nullptr)
    {
        throw new InvalidArgsEx("BinaryTreeNode::insertLeft", "*to_insert is null");
    }

    //insert...
    to_insert->upper = this;
    to_insert->onBranchOfUpper = right_branch;
    this->right = to_insert;
}

// ---------------- deleters ---------------------

void BinaryTreeNode::deleteSubtree()
{
    if(this->left != nullptr) this->left->deleteSubtree();
    if(this->right != nullptr) this->right->deleteSubtree();
    delete this;
}

// ------------------------ booleans -------------------------

bool BinaryTreeNode::isRoot()
{
    return (this->upper == nullptr);
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
