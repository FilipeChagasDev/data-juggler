#ifndef STACK_CXX
#define STACK_CXX
#

#include "stack.hpp"

namespace DataJuggler {

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

//#endif
