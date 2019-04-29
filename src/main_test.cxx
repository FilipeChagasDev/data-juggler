#include <iostream>
#include "stringhash.hpp"
#include "linkedlistnode.hpp"
#include "treenode.hpp"
#include "list.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include "keyingtree.hpp"
#include "exception.hpp"
#include <cstdlib>

/*
 * This file is just a draft that I (Filipe Chagas) use to make the unit tests.
 * Look in the unit-tests directory for more organized and careful unit tests.
*/

#define CLEANSCREEN system("clear");
using namespace std;

void manual_test_string_hash_generator();
void manual_test_linear();
void manual_test_treenode();
void manual_test_list();
void manual_test_stack();
void manual_test_queue();
void manual_test_keyingtree();

int main()
{
    //manual_test_string_hash_generator();
    //manual_test_linear();
    //manual_test_treenode();
    //manual_test_list();
    //manual_test_stack();
    //manual_test_queue();
    manual_test_keyingtree();

    return 0;
}

void manual_test_keyingtree()
{
   DataJuggler::KeyingTree<unsigned long, string> *kt = new DataJuggler::KeyingTree<unsigned long, string>();
   kt->insert(6, "filipe");
   kt->insert(2, "joao");
   kt->insert(7, "andre");
   cout << " ----- belongingData ----" << endl;
   cout << (kt->belongingData("filipe") == true ? "true" : "false") << endl;
   cout << (kt->belongingData("joao") == true ? "true" : "false") << endl;
   cout << (kt->belongingData("andre") == true ? "true" : "false") << endl;
   cout << (kt->belongingData("mauro") == true ? "true" : "false") << endl;

   cout << " ----- find ----" << endl;
   cout << kt->find(7) << endl;
   cout << kt->find(2) << endl;
   try
   {
       kt->find(3);
   }
   catch (DataJuggler::Exception *ex)
   {
        cout << "Exception: " << ex->name << endl;
   }

    cout << " ----- forEach ----" << endl;
    kt->forEach([](unsigned long key, string str)->bool
    {
        cout << "key: " << key << " | str: " << str << endl;
        return false;
    });

    kt->remove(2);
    //kt->remove(6);
    //kt->remove(7);

    cout << " ----- forEach ----" << endl;
    kt->forEach([](unsigned long key, string str)->bool
    {
        cout << "key: " << key << " | str: " << str << endl;
        return false;
    });

    cout << " ----- forEachNode ----" << endl;
    kt->forEachNode([](DataJuggler::KeyingTreeNode<unsigned long, string> *node)->bool
    {
        node->data = "_" + node->data + "_";
        return false;
    });

    cout << " ----- forEach ----" << endl;
    kt->forEach([](unsigned long key, string str)->bool
    {
        cout << "key: " << key << " | str: " << str << endl;
        return false;
    });

    kt->insert(2, "gogug");
    kt->insert(1, "lup");
    DataJuggler::KeyingTreeNode<unsigned long, string> *node = kt->findNode(6);
    kt->removeNode(node);

    cout << " ----- forEach ----" << endl;
    kt->forEach([](unsigned long key, string str)->bool
    {
        cout << "key: " << key << " | str: " << str << endl;
        return false;
    });

    cout << "------ erasing with removeNode ------" << endl;
    kt->forEachNode([&](DataJuggler::KeyingTreeNode<unsigned long, string> *node)->bool
    {
        cout << " -----" << endl;
        kt->forEach([](unsigned long key, string str)->bool
        {
            cout << "key: " << key << " | str: " << str << endl;
            return false;
        });

        kt->removeNode(node);
        return false;
    });

    for(unsigned long i = 1; i < 10; i++)
    {
        string str = "aaa";
        str[0] += i;
        str[1] += i + 1;
        str[2] += i + 2;
        DataJuggler::KeyingTreeNode<unsigned long, string> *nnode = new DataJuggler::KeyingTreeNode<unsigned long, string>(i,str);
        kt->insertNode(nnode);
    }

    cout << " ----- forEach ----" << endl;
    kt->forEach([&](unsigned long key, string str)->bool
    {
        cout << "key: " << key << " | str: " << str << endl;
        cout << ( kt->belongingData(str) == true ? "true" : "false" ) << endl;
        return false;
    });

    cout << " ----- forEachNode ----" << endl;
    kt->forEachNode([&](DataJuggler::KeyingTreeNode<unsigned long, string> *node)->bool
    {
        cout << "key: " << node->key << " | str: " << node->data << endl;
        cout << ( kt->belongingNode(node) == true ? "true" : "false" ) << endl;
        return false;
    });

    DataJuggler::KeyingTreeNode<unsigned long, string> *fakenode = new DataJuggler::KeyingTreeNode<unsigned long, string>(50,"jhvdiu");
    cout << ( kt->belongingNode(fakenode) == true ? "true" : "false" ) << endl;

    delete kt;

    cout << "memory leakage test " << endl;
    while (1)
    {
        DataJuggler::KeyingTree<int,string> *t = new DataJuggler::KeyingTree<int,string>();
        for(int i = 0; i < 10000; i++) t->insert(i,"__________________________________________________________________________");
        delete t;
    }
}

void manual_test_queue()
{
    DataJuggler::Queue<int> *queue = new DataJuggler::Queue<int>();

    for(int i = 0; i < 10; i++)
    {
        cout << "push: " << i << endl;
        queue->push(i);
        for(DataJuggler::LinkedListItem<int> *j = queue->getFirstNode();
            j != nullptr; DataJuggler::LinkedListItem<int>::goForward(&j))
        {
            cout << j->data << "<->";
        }
        cout << endl;
    }

    cout << "------------------------------" << endl;

    for(int i = 0; i < 10; i++)
    {
        for(DataJuggler::LinkedListItem<int> *j = queue->getFirstNode();
            j != nullptr; DataJuggler::LinkedListItem<int>::goForward(&j))
        {
            cout << j->data << "<->";
        }

        cout << endl << "peek: " << queue->peek() << endl;
        cout << "pop: " << queue->pop() << endl;
    }
}

void manual_test_stack()
{
    DataJuggler::Stack<int> *stack = new DataJuggler::Stack<int>();

    for(int i = 0; i < 10; i++)
    {
        cout << "push: " << i << endl;
        stack->push(i);
        for(DataJuggler::LinkedListItem<int> *j = stack->getFirstNode();
            j != nullptr; DataJuggler::LinkedListItem<int>::goForward(&j))
        {
            cout << j->data << "<->";
        }
        cout << endl;
    }

    cout << "------------------------------" << endl;

    for(int i = 0; i < 10; i++)
    {
        for(DataJuggler::LinkedListItem<int> *j = stack->getFirstNode();
            j != nullptr; DataJuggler::LinkedListItem<int>::goForward(&j))
        {
            cout << j->data << "<->";
        }

        cout << endl << "peek: " << stack->peek() << endl;
        cout << "pop: " << stack->pop() << endl;
    }
}

// ------------ List ------------------

void manual_test_list()
{
    DataJuggler::List<int> *list = new DataJuggler::List<int>();

    for(int i = 0; i < 5; i++)
    {
        list->insertBegin(5 - i);
        list->insertEnd(5 + i + 1);
    }

    for(DataJuggler::LinkedListItem<int> *i = list->getFirstNode();
        i != nullptr;
        i = static_cast<DataJuggler::LinkedListItem<int>*>(i->getNext()))
    {
        cout << i->data << "<->";
    }

}

// ------- BinaryTreeNode tester --------

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

void manual_test_treenode()
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
            return;
        }
    }
}

// ------- LinearNode tester ---------

class IntNode : public DataJuggler::LinkedListNode
{
    public:
        int data;
        IntNode(LinkedListNode::Header *h);
        ~IntNode();
};

IntNode::IntNode(LinkedListNode::Header *h) : DataJuggler::LinkedListNode(h)
{
}

IntNode::~IntNode()
{
}

void manual_test_linear()
{
    DataJuggler::LinkedListNode::Header *h = new DataJuggler::LinkedListNode::Header();
    IntNode *curnode = new IntNode(h);
    curnode->insertItSingle();
    curnode->data = 0;
    int answer;

    while(true)
    {
        for(IntNode *it = static_cast<IntNode*>(h->first);
            it != nullptr;
            it = static_cast<IntNode*>(it->getNext()))
        {
            if(it == curnode) cout << "[" << it->data << "]" << "<->";
            else cout << it->data << "<->";
        }

        cout << endl << endl;

        cout << "1 - insert a node after here" << endl
             << "2 - insert a node before here" << endl
             << "3 - remove this node" << endl
             << "4 - select next node" << endl
             << "5 - select prev node" << endl;
        cin >> answer;

        switch (answer)
        {
            case 1:
            {
                IntNode *newnode = new IntNode(h);
                cout << "choose a int value: ";
                cin >> answer;
                newnode->data = answer;
                curnode->insertAfter(newnode);
                break;
            }

            case 2:
            {
                IntNode *newnode = new IntNode(h);
                cout << "choose a int value: ";
                cin >> answer;
                newnode->data = answer;
                curnode->insertBefore(newnode);
                break;
            }

            case 3:
            {
                IntNode *corner;

                if(curnode->getPrevious() != nullptr)
                    corner = static_cast<IntNode*>(curnode->getPrevious());
                else
                    corner = static_cast<IntNode*>(curnode->getNext());

                curnode->remove();
                curnode = corner;

                if(curnode == nullptr)
                {
                    cout << "linear is empty" << endl;
                    return;
                }

                break;
            }

            case 4:
            {
                if(curnode->getNext() == nullptr)
                {
                    cout << "end of list" << endl;
                }
                else curnode =  static_cast<IntNode*>(curnode->getNext());

                break;
            }

            case 5:
            {
                if(curnode->getPrevious() == nullptr)
                {
                    cout << "begin of list" << endl;
                }
                else curnode =  static_cast<IntNode*>(curnode->getPrevious());

                break;
            }
        }

        CLEANSCREEN;
    }
}


// ----------- hash generator test --------------

void manual_test_string_hash_generator()
{
    string s;
    cout << "test of string hash generator..."  << endl;
    while (true)
    {
        cout << "type a string" << endl;
        cin >> s;
        cout << DataJuggler::getStringHash(DataJuggler::name_charset, s ) << endl;
    }
}
