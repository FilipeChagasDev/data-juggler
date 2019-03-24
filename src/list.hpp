#ifndef LIST_HPP
#define LIST_HPP

#include "linkedlistitem.hpp"
#include "linkedlistnode.hpp"
#include "exception.hpp"

namespace DataJuggler {

/** This function represents a linked list of data */
template<typename datatype>
class List : LinkedListNode::Header
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

}//end of namespace

#endif // LIST_HPP
