#include "linkedlistitem.hpp"

namespace DataJuggler {

template<typename datatype>
LinkedListItem<datatype>::LinkedListItem(LinkedListNode::Header *header, datatype data) : LinkedListNode(header)
{
    this->data = data;
}

template<typename datatype>
void LinkedListItem<datatype>::CloneFrom(LinkedListNode *to_copy)
{
    if(to_copy == nullptr) throw new InvalidArgsEx("LinkedListItem<datatype>::CloneFrom", "*to_copy is null");
    LinkedListItem<datatype> *node = dynamic_cast<LinkedListItem<datatype>*>(to_copy);

    LinkedListNode::CloneFrom(to_copy);
    if(node != nullptr)
    {
        this->data = node->data;
    }
}


}//end of namespace
