#ifndef LINKEDLISTITEM_H
#define LINKEDLISTITEM_H

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
    /** Make it a copy of another LinkedListItem (object from pointer)*/
    virtual void CloneFrom(LinkedListNode *to_copy);
};

} //end of namespace
#endif // LINKEDLISTITEM_H
