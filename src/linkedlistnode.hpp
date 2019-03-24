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
                Header();
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

        /** This destructor removes the node from the list and then deletes it.
        The list is not broken, as this destructor "joins" the neighboring nodes
        of this one before doing the deletion. */
        virtual ~LinkedListNode();

        /** whether the list is empty, this function insert this as only node.
        If list is not empty, it will throw a LinkedListNotEmptyEx.
        If node does not have header, it will throw a LinkedListNodeWithoutHeaderEx.*/
        void insertItSingle();

        /** Make it a copy of another LinkedListNode (object from pointer).*/
        virtual void CloneFrom(LinkedListNode *to_copy);

        /** Make it a copy of another LinkedListNode (object from reference). */
        //virtual void CloneFrom(LinkedListNode &to_copy);

        /** Insert a node after this in linked list.*/
        void insertAfter(LinkedListNode *to_insert);

        /** Insert a node before this in linked list.*/
        void insertBefore(LinkedListNode *to_insert);

        /** Remove this node from the linked list (without delete this).
        This function "joins" its neighbor nodes, making this node no longer in the list thread.*/
        void remove();

        /** Move this node to after of a reference node of the same list. */
        void moveToAfterOf(LinkedListNode *ref_node);

        /** Move this node to before of a reference node of the same list. */
        void moveToBeforeOf(LinkedListNode *ref_node);

        /** Get the next node of this in the list. */
        LinkedListNode *getNext();

        /** Get the previous node of this in the list. */
        LinkedListNode *getPrevious();

        /** Get the list header */
        LinkedListNode::Header *getHeader();

        /** Checks for logical errors in the linked list. */
        void checkIntegrity();
};

/** This class represents an exception that is thrown when the node does not have header and program
attempts to perform an operation with the node that requires header */
class LinkedListNodeWithoutHeaderEx : public Exception
{
    public:
        LinkedListNodeWithoutHeaderEx();
        static const unsigned long long defaultCode = 26363;
};

/** This class represents an exception that is thrown when the program tries to perform an operation that
is only allowed when the list is empty, but the list is not empty. */
class LinkedListNotEmptyEx : public Exception
{
    public:
        LinkedListNotEmptyEx();
        static const unsigned long long defaultCode = 12572;
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
