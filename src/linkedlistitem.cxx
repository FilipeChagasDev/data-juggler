#ifndef LINKEDLISTITEM_CXX
#define LINKEDLISTITEM_CXX
#

#include "linkedlistitem.hpp"

namespace DataJuggler {

template<typename datatype>
LinkedListItem<datatype>::LinkedListItem(LinkedListNode::Header *header, datatype data) : LinkedListNode(header)
{
    this->data = data;
}


}//end of namespace

#endif
