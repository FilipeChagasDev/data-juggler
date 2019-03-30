#ifndef DJ_LIST_HPP
#define DJ_LIST_HPP

#include "linkedlistitem.hpp"
#include "linkedlistnode.hpp"
#include "exception.hpp"

namespace DataJuggler {

/** This function represents a linked list of data */
template<typename datatype>
class List : public LinkedListNode::Header
{
public:
    List();

    /** This function creates a new node for this list without insert it */
    LinkedListItem<datatype> *createNode(datatype data);

    /** Returns true whether the list is empty */
    bool isEmpty();

    /** This function creates a new node with the data passed as an argument and inserts in the begin of this list */
    void insertBegin(datatype data);

    /** This functions inserts the node passed as argument in the begin of this list */
    void insertNodeBegin(LinkedListItem<datatype> *node);

    /** This function creates a new node with the data passed as an argument and inserts in the end of this list */
    void insertEnd(datatype data);

    /** This functions inserts the node passed as argument in the end of this list */
    void insertNodeEnd(LinkedListItem<datatype> *node);

    /** This function returns the number of nodes in this list */
    unsigned long getCounter();

    /** This function returns the first node of this list */
    LinkedListItem<datatype> *getFirstNode();

    /** This function returns the last node of this list */
    LinkedListItem<datatype> *getLastNode();
};

// ---------------------- implementation -----------------------------

template<typename datatype>
List<datatype>::List() : LinkedListNode::Header()
{
}

template<typename datatype>
LinkedListItem<datatype>* List<datatype>::createNode(datatype data)
{
    LinkedListItem<datatype> *node = new LinkedListItem<datatype>(this, data);
}

// -------------------------- booleans -----------------------------

template<typename datatype>
bool List<datatype>::isEmpty()
{
    return (this->first == nullptr);
}

// -------------------------- getters ----------------------------

template<typename datatype>
LinkedListItem<datatype>* List<datatype>::getFirstNode()
{
    return static_cast<LinkedListItem<datatype>*>(this->first);
}

template<typename datatype>
LinkedListItem<datatype>* List<datatype>::getLastNode()
{
    return static_cast<LinkedListItem<datatype>*>(this->last);
}

template<typename datatype>
unsigned long List<datatype>::getCounter()
{
    return this->counter;
}

// ------------------------- inserters ----------------------------

template <typename datatype>
void List<datatype>::insertNodeBegin(LinkedListItem<datatype> *node)
{
    if(node == nullptr) throw new InvalidArgsEx("List<datatype>::insertNodeBegin", "*node is null");

    if(static_cast<List<datatype>*>(node->getHeader()) != this)
        throw new InvalidArgsEx("List<datatype>::insertNodeBegin", "*node does not have this header");

    if(this->isEmpty())
    {
        node->insertItSingle();
    }
    else
    {
        static_cast<LinkedListItem<datatype>*>(this->first)->insertBefore(node);
    }
}

template <typename datatype>
void List<datatype>::insertNodeEnd(LinkedListItem<datatype> *node)
{
    if(node == nullptr) throw new InvalidArgsEx("List<datatype>::insertNodeBegin", "*node is null");

    if(static_cast<List<datatype>*>(node->getHeader()) != this)
        throw new InvalidArgsEx("List<datatype>::insertNodeBegin", "*node does not have this header");

    if(this->isEmpty())
    {
        node->insertItSingle();
    }
    else
    {
        static_cast<LinkedListItem<datatype>*>(this->last)->insertAfter(node);
    }
}


template <typename datatype>
void List<datatype>::insertBegin(datatype data)
{
    this->insertNodeBegin(this->createNode(data));
}

template <typename datatype>
void List<datatype>::insertEnd(datatype data)
{
    this->insertNodeEnd(this->createNode(data));
}

}//end of namespace

#endif // LIST_HPP
