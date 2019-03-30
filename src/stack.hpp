#ifndef STACK_HPP
#define STACK_HPP

#include "list.hpp"

namespace DataJuggler {

/** LIFO list. Nodes are inserted at the beginning of the list with push and removed from the beginning of the list with pop.*/
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

// ------ implementation -------

template<typename datatype>
Stack<datatype>::Stack()
{
}

template <typename datatype>
LinkedListItem<datatype>* Stack<datatype>::push(datatype data)
{
    this->insertBegin(data);
    return static_cast<LinkedListItem<datatype>*>(this->first);
}

template <typename datatype>
datatype Stack<datatype>::peek()
{
    return static_cast<LinkedListItem<datatype>*>(this->first)->data;
}

template <typename datatype>
datatype Stack<datatype>::pop()
{
    LinkedListItem<datatype>* removed_node = static_cast<LinkedListItem<datatype>*>(this->first);
    datatype removed_data = removed_node->data;
    delete removed_node;
    return removed_data;
}

template <typename datatype>
void Stack<datatype>::pushNode(LinkedListItem<datatype> *node)
{
    if(node == nullptr) throw new InvalidArgsEx("Stack::pushNode","*node is null");
    this->insertNodeBegin(node);
}

template <typename datatype>
LinkedListItem<datatype>* Stack<datatype>::popNode()
{
    LinkedListItem<datatype>* removed_node = static_cast<LinkedListItem<datatype>*>(this->first);
    removed_node->remove();
    return removed_node;
}

template <typename datatype>
LinkedListItem<datatype>* Stack<datatype>::peekNode()
{
    LinkedListItem<datatype>* removed_node = static_cast<LinkedListItem<datatype>*>(this->first);
    return removed_node;
}

}//end of namespace

#endif // STACK_HPP
