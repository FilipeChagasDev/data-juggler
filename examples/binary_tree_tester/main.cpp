#include <iostream>
#include <datajuggler.hpp>
//#include "../../datajuggler.hpp"

#define CLEANSCREEN system("clear")

class IntTreeNode : public DataJuggler::BinaryTreeNode
{
    public:
        int data;
        IntTreeNode(int data);
};

IntTreeNode::IntTreeNode(int data) : DataJuggler::BinaryTreeNode()
{
    this->data = data;
}

void show_tree(IntTreeNode *tn, IntTreeNode *root, int counter)
{
#define ESPACO for(int i = 0; i < counter-1; i++) cout << "´\t";
    //for(int i = 0; i < counter; i++) cout << " ";

    if(tn == nullptr)
    {
        ESPACO;
        cout << "null" << endl;
        return;
    }

    ESPACO;
    cout << "data:" << tn->data;
    cout << endl;

    ESPACO;
    cout << "depth:" << tn->getDistanceTo(root);
    cout << endl;

    ESPACO;
    cout << "left:{";
    cout << endl;

    show_tree(static_cast<IntTreeNode*>(tn->getLeft()), root, counter+1);

    ESPACO;
    cout << "}";
    cout << endl;

    ESPACO;
    cout << "right:{";
    cout << endl;

    show_tree(static_cast<IntTreeNode*>(tn->getRight()), root, counter+1);

    ESPACO;
    cout << "}";
    cout << endl;
}

int main()
{
    IntTreeNode *root = new IntTreeNode(-1);
    IntTreeNode *tree = root;

    //Construct tree randomly
    for(int i = 0; i < 5; i++)
    {
        srand((unsigned int)clock());
        switch(rand()%2)
        {
            case 0:
            {
                tree->insertLeft(new IntTreeNode(i));
                break;
            }

            case 1:
            {
                tree->insertRight(new IntTreeNode(i));

                break;
            }
        }

        switch(rand()%3)
        {
            case 0:
            {
                if(tree->getLeft() != nullptr)
                    tree = static_cast<IntTreeNode*>(tree->getLeft());
                break;
            }

            case 1:
            {
                if(tree->getRight() != nullptr)
                    tree = static_cast<IntTreeNode*>(tree->getRight());
                break;
            }

            default:{}
        }
    }

    //Options
    while (1)
    {
        CLEANSCREEN;
        cout << "current tree:" << endl;
        show_tree(root, root, 1);
        cout << "Deeper leaf data: " << static_cast<IntTreeNode*>(root->getDeeperSubtreeLeaf())->data << endl;
        cout << "Set a node to remove whith these commands: gotoright, gotoleft, delete" << endl;
        IntTreeNode *current = root;
        string cmd;
        do
        {
            cout << "current node data:" << current->data << endl;
            cin >> cmd;
            if(cmd == "gotoright")
            {
                if(current->getRight() == nullptr)
                {
                    cout << "error: nullptr" << endl;
                    continue;
                }

                current = static_cast<IntTreeNode*>(current->getRight());
            }
            else if(cmd == "gotoleft")
            {
                if(current->getLeft() == nullptr)
                {
                    cout << "error: nullptr" << endl;
                    continue;
                }

                current = static_cast<IntTreeNode*>(current->getLeft());
            }
            else
            {
                cout << "undefined command" << endl;
            }

        }while(cmd != "delete");

        current->deleteSubtree();

        if(current == root)
        {
            cout << "tree deleted" << endl;
            return 0;
        }
    }

    return 0;
}
