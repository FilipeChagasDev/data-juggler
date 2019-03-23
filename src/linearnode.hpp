#ifndef LINEARNODE_H
#define LINEARNODE_H

#include "exception.hpp"

namespace DataJuggler {


/** This class represents the double-linked node of a list structure.
This class is basic and should not be instantiated directly. Subclasses of this can be used to insert data into the node. */
class LinkedListNode
{

    public:
        /** This class represents the header of a list formed by LinkedListNodes. */
        class Header
        {
            public:
                unsigned long counter;
                LinkedListNode *first;
                LinkedListNode *last;
        };

    protected:
        LinkedListNode::Header *extern_header;
        LinkedListNode *next;
        LinkedListNode *previous;

    public:
        /** This constructor takes as an argument a pointer to the list header */
        LinkedListNode(LinkedListNode::Header *extern_header);

         /** This constructor takes as an argument a reference to the list header */
        LinkedListNode(LinkedListNode::Header &extern_header);

        virtual ~LinkedListNode(); //TODO destructor

        /** Make it a copy of another LinkedListNode (object from pointer)*/
        virtual void CloneFrom(LinkedListNode *to_copy);

        /** Make it a copy of another LinkedListNode (object from reference) */
        virtual void CloneFrom(LinkedListNode &to_copy);

        /** Insert a node after this in linked list*/
        void insertAfter(LinkedListNode *to_insert);

        /** Insert a node before this in linked list*/
        void insertBefore(LinkedListNode *to_insert);

        /** Remove this node from the linked list (without delete this)*/
        void remove();

        /** Move this node to after of a reference node of the same list */
        void moveToAfterOf(LinkedListNode *ref_node);

        /** Move this node to before of a reference node of the same list */
        void moveToBeforeOf(LinkedListNode *ref_node);

        /** Get the next node of this in the list */
        LinkedListNode *getNext();

        /** Get the previous node of this in the list */
        LinkedListNode *getPrevious();

        /** Checks for logical errors in the linked list */
        void checkIntegrity();
};

/** This class represents an exception caused by a logical error in a linked list. When a logical
error is detected in the linked list, this class is instantiated and an exception is thrown with it.    */
class DamagedLinkedListEx : public Exception
{
    public:
        LinkedListNode *node_where_throwed;
        DamagedLinkedListEx(LinkedListNode *node_where_throwed);
        static const unsigned long long defaultCode = 11246;
};

} //end of DataJuggler namespace
#endif // LINEARNODE_H
