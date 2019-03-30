#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "list.hpp"
#include "exception.hpp"

namespace DataJuggler{

/** FIFO list. Nodes are inserted at the ending of the list with push and removed from the beginning of the list with pop.*/
template <typename datatype>
class Queue : public List<datatype>
{
    public:
        Queue();

        /** This function creates a new node with the argument data and insert it in the end of list.*/
        LinkedListItem<datatype> *push(datatype data);

        /** This function returns the data from the first node of the list */
        datatype peek();

        /** This function removes the first node of the list and returns the data from the removed node*/
        datatype pop();

        /** This function inserts the argument node in the end of list */
        void pushNode(LinkedListItem<datatype> *node);

        /** This function removes and return the first node of the list */
        LinkedListItem<datatype> *popNode();

        /** This function returns the first node of the list */
        LinkedListItem<datatype> *peekNode();
};

// -------------- Implementation -----------------

template <typename datatype>
Queue<datatype>::Queue()
{
}

template <typename datatype>
LinkedListItem<datatype>* Queue<datatype>::push(datatype data)
{
    this->insertEnd(data);
    return static_cast<LinkedListItem<datatype>*>(this->last);
}

template <typename datatype>
datatype Queue<datatype>::peek()
{
    return static_cast<LinkedListItem<datatype>*>(this->first)->data;
}

template <typename datatype>
datatype Queue<datatype>::pop()
{
    LinkedListItem<datatype>* removed_node = static_cast<LinkedListItem<datatype>*>(this->first);
    datatype removed_data = removed_node->data;
    delete removed_node;
    return removed_data;
}

template <typename datatype>
void Queue<datatype>::pushNode(LinkedListItem<datatype> *node)
{
    if(node == nullptr) throw new InvalidArgsEx("Queue::pushNode","*node is null");
    this->insertNodeEnd(node);
}

template <typename datatype>
LinkedListItem<datatype>* Queue<datatype>::popNode()
{
    LinkedListItem<datatype>* removed_node = static_cast<LinkedListItem<datatype>*>(this->first);
    removed_node->remove();
    return removed_node;
}

template <typename datatype>
LinkedListItem<datatype>* Queue<datatype>::peekNode()
{
    LinkedListItem<datatype>* removed_node = static_cast<LinkedListItem<datatype>*>(this->first);
    return removed_node;
}


} //end of namespace

#endif // QUEUE_HPP
