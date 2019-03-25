#ifndef LINKEDLISTITEM_HPP
#define LINKEDLISTITEM_HPP

#include "linkedlistnode.hpp"
#include "exception.hpp"

namespace DataJuggler {

/** This class represents a node of a linked list with a data.
The type of this data must be specified in the template when instantiating this class */
template<typename datatype>
class LinkedListItem : public LinkedListNode
{
public:
    datatype data;

    /** This constructor receives, as an argument, a pointer to the list header and a data to the node */
    LinkedListItem(LinkedListNode::Header *header, datatype data);
};

} //end of namespace

#include "linkedlistitem.cxx"

#endif // LINKEDLISTITEM_H
