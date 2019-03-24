#include "list.hpp"

namespace DataJuggler {

template<typename datatype>
List<datatype>::List() : LinkedListNode::Header()
{
}

template<typename datatype>
LinkedListItem<datatype>* List<datatype>::createNode(datatype data)
{
    LinkedListItem<datatype>* node = new LinkedListItem<datatype>(this, data);
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
    return this->first;
}

template<typename datatype>
LinkedListItem<datatype>* List<datatype>::getLastNode()
{
    return this->last;
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

    if(node->extern_header != this)
        throw new InvalidArgsEx("List<datatype>::insertNodeBegin", "*node does not have this header");

    if(this->isEmpty())
    {
        node->insertItSingle();
    }
    else
    {
        static_cast<LinkedListItem<datatype>*>(node)->insertBefore(node);
    }
}

template <typename datatype>
void List<datatype>::insertNodeEnd(LinkedListItem<datatype> *node)
{
    if(node == nullptr) throw new InvalidArgsEx("List<datatype>::insertNodeBegin", "*node is null");

    if(node->extern_header != this)
        throw new InvalidArgsEx("List<datatype>::insertNodeBegin", "*node does not have this header");

    if(this->isEmpty())
    {
        node->insertItSingle();
    }
    else
    {
        static_cast<LinkedListItem<datatype>*>(node)->insertAfter(this->last);
    }
}


template <typename datatype>
void List<datatype>::insertBegin(datatype data)
{
    this->insertBegin(this->createNode(data));
}

template <typename datatype>
void List<datatype>::insertEnd(datatype data)
{
    this->insertEnd(this->createNode(data));
}


}//end of namespace
