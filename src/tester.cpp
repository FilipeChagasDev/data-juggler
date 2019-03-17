#include <iostream>
#include "stringhash.hpp"
#include "linearnode.hpp"

using namespace std;

void manual_test_string_hash_generator();
void manual_test_linear();

int main()
{
    //manual_test_string_hash_generator();
    manual_test_linear();
    return 0;
}

// ------- LinearNode tester ---------

class IntNode : public DataJuggler::LinearNode
{
    public:
        int data;
        IntNode(LinearNode::Header *h);
        ~IntNode();
};

IntNode::IntNode(LinearNode::Header *h) : DataJuggler::LinearNode(h)
{
}

IntNode::~IntNode()
{
}

void manual_test_linear()
{
    DataJuggler::LinearNode::Header *h = new DataJuggler::LinearNode::Header();
    IntNode *curnode = new IntNode(h);
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

        system("clear");
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
