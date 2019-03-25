#ifndef STACK_HPP
#define STACK_HPP

#include "list.hpp"

namespace DataJuggler {

/** LIFO list. Nodes are inserted at the beginning of the list with push and removed from the top of the list with pop.*/
template <typename datatype>
class Stack : public List<datatype>
{
public:
    Stack();

    /** This function creates a new node with the argument data and insert it in the begin of list.*/
    LinkedListItem<datatype> *push(datatype data);

    /** This function returns the data from the first node of the list */
    datatype peek();

    /** This function removes the first node of the list and returns the data from the removed node*/
    datatype pop();

    /** This function inserts the argument node in the begin of list */
    void pushNode(LinkedListItem<datatype> *node);

    /** This function removes and return the first node of the list */
    LinkedListItem<datatype> *popNode();

    /** This function returns the first node of the list */
    LinkedListItem<datatype> *peekNode();
};

}//end of namespace

#include "stack.cxx"

#endif // STACK_HPP
