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

    /** This static function receives as an argument a pointer-to-pointer that references a
    LinkedListItem and causes this pointer-to-pointer to refer to the next LinkedListItem.
    It is useful in iterative algorithms, in which there is an iterator pointer, which "advances"
    its reference to each repetition of the algorithm using a "node <- node.next" operation.
    The goFoward function does this operation "node <- node.next" internally, with the iterator
    that it received by reference as argument. Suppose the iterator pointer is declared as
    "LinkedListItem<int> *i = list->getFirstNode ()" ... the goForward function should be used
    in this case as follows: "LinkedListItem<int>::goForward(&i)". */
    static void goForward(LinkedListItem<datatype> **ptr);

    /** It does a resembling goForward operation, with the difference that it walks backwards
    with the iterator instead of walking forward. */
    static void goBack(LinkedListItem<datatype> **ptr);
};

/** Exception that is throwed when an attempt to walk with an iterator that points to a null node is made */
class NullIteratorEx : public Exception
{
    public:
        NullIteratorEx();
        static const unsigned long defaultCode = 6145;
};


// -------- implementation ---------

NullIteratorEx::NullIteratorEx()
    :Exception (NullIteratorEx::defaultCode, "Null Iterator Exception",
                "An attempt to walk with an iterator that points to a null node was made")
{
}


template<typename datatype>
LinkedListItem<datatype>::LinkedListItem(LinkedListNode::Header *header, datatype data) : LinkedListNode(header)
{
    this->data = data;
}

template<typename datatype>
void LinkedListItem<datatype>::goForward(LinkedListItem<datatype> **ptr)
{
    if(ptr == nullptr) throw new InvalidArgsEx("LinkedListItem::goFoward", "**ptr is null");
    if(*ptr == nullptr) throw new NullIteratorEx();
    *ptr = static_cast<LinkedListItem<datatype>*>((*ptr)->getNext());
}


template<typename datatype>
void LinkedListItem<datatype>::goBack(LinkedListItem<datatype> **ptr)
{
    if(ptr == nullptr) throw new InvalidArgsEx("LinkedListItem::goFoward", "**ptr is null");
    if(*ptr == nullptr) throw new NullIteratorEx();
    *ptr = static_cast<LinkedListItem<datatype>*>((*ptr)->gePrevious());
}

} //end of namespace

#endif // LINKEDLISTITEM_H
