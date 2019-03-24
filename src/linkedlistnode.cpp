#include "linkedlistnode.hpp"

namespace DataJuggler {

LinkedListNodeWithoutHeaderEx::LinkedListNodeWithoutHeaderEx()
    :Exception (LinkedListNodeWithoutHeaderEx::defaultCode, "Linked List Node Without Header Exception",
                "node has no header and the program attempted to perform an operation with the node that requires header")
{
}

DamagedLinkedListEx::DamagedLinkedListEx(LinkedListNode *node_where_throwed)
    :Exception(DamagedLinkedListEx::defaultCode, "Damaged Linked List Exception",
               "A fault in the linked list structure was detected. Analyze the source code of the LinkedListNode class or its subclass.")
{
    this->node_where_throwed = node_where_throwed;
}

LinkedListNotEmptyEx::LinkedListNotEmptyEx()
    :Exception(LinkedListNotEmptyEx::defaultCode, "Linked List Not Empty Exception",
               "The program tried to perform an operation that is only allowed when the list is empty, but the list is not empty.")
{
}

LinkedListNode::Header::Header()
{
    this->first = nullptr;
    this->last = nullptr;
    this->counter = 0;
}

// ---------- Constructors ------------

LinkedListNode::LinkedListNode(LinkedListNode::Header *extern_header)
{
    this->extern_header = extern_header;
    this->next = nullptr;
    this->previous = nullptr;
}

LinkedListNode::LinkedListNode(LinkedListNode::Header &extern_header)
{
    this->extern_header = &extern_header;
    this->next = nullptr;
    this->previous = nullptr;
}

// ------------ Destructors -------------

LinkedListNode::~LinkedListNode()
{
    this->remove();
}

// ------------- Cloners -----------------

void LinkedListNode::CloneFrom(LinkedListNode *to_copy)
{
    this->extern_header = to_copy->extern_header;
    this->next = to_copy->next;
    this->previous = to_copy->previous;
}

/*void LinkedListNode::CloneFrom(LinkedListNode &to_copy)
{
    this->extern_header = to_copy.extern_header;
    this->next = to_copy.next;
    this->previous = to_copy.previous;
}*/

// ------------- Inserters ---------------

void LinkedListNode::insertItSingle()
{
    if(this->extern_header != nullptr)
    {
        if(this->extern_header->first == nullptr && this->extern_header->last == nullptr)
        {
            this->extern_header->first = this;
            this->extern_header->last = this;
            this->extern_header->counter++;
        }
        else
        {
            throw new LinkedListNotEmptyEx();
        }
    }
    else
    {
        throw new LinkedListNodeWithoutHeaderEx();
    }
}

void LinkedListNode::insertAfter(LinkedListNode *to_insert)
{
    bool im_the_last = (this->next == nullptr);
    bool have_header = (this->extern_header != nullptr);

    //check for errors
    if(to_insert == nullptr)
    {
        throw new InvalidArgsEx("LinkedListNode::insertAfter", "*to_insert is null");
    }

    this->checkIntegrity();

    //lets go to what matters...

    to_insert->next = this->next;
    to_insert->previous = this;

    if(!im_the_last) //true whether this is not the last
    {
        this->next->previous = to_insert;
    }
    else
    { //do it whether this is the last
        if(have_header) this->extern_header->last = to_insert;
    }

    this->next = to_insert;
    if(have_header) this->extern_header->counter++;
}


void LinkedListNode::insertBefore(LinkedListNode *to_insert)
{
    bool im_the_first = (this->previous == nullptr);
    bool have_header = (this->extern_header != nullptr);

    //check for errors
    if(to_insert == nullptr)
    {
        throw new InvalidArgsEx("LinkedListNode::insertAfter", "*to_insert is null");
    }

    this->checkIntegrity();

    //lets go to what matters...
    to_insert->next = this;
    to_insert->previous = this->previous;

    if(!im_the_first) //true whether this is not the first
    {
        this->previous->next = to_insert;
    }
    else
    { //do it whether this is the first
        if(have_header) this->extern_header->first = to_insert;
    }

    this->previous = to_insert;
    if(have_header) this->extern_header->counter++;
}

void LinkedListNode::remove()
{
    bool im_the_first = (this->previous == nullptr);
    bool im_the_last = (this->next == nullptr);
    bool have_header = (this->extern_header != nullptr);

    //check for errors
    this->checkIntegrity();

    //lets go to what matters...
    LinkedListNode *my_next = this->next;
    LinkedListNode *my_previous = this->previous;

    if(!im_the_first) my_previous->next = my_next; //do it whether this is not the first
    else if(have_header) this->extern_header->first = my_next; //do it whether this is the first

    if(!im_the_last) my_next->previous = my_previous; //do it whether this is not the last
    else if(have_header) this->extern_header->last = my_previous; //do it whether this is the last

    this->next = nullptr;
    this->previous = nullptr;
    if(have_header) this->extern_header->counter--;
}

void LinkedListNode::moveToAfterOf(LinkedListNode *ref_node)
{
    this->remove();
    ref_node->insertAfter(this);
}

void LinkedListNode::moveToBeforeOf(LinkedListNode *ref_node)
{
    this->remove();
    ref_node->insertBefore(this);
}

void LinkedListNode::checkIntegrity()
{
    bool im_the_first = (this->previous == nullptr);
    bool im_the_last = (this->next == nullptr);
    bool have_header = (this->extern_header != nullptr);

    if(have_header)
    {
        if(im_the_first && this->extern_header->first != this)
        {
            throw new DamagedLinkedListEx(this);
        }

        if(im_the_last && this->extern_header->last != this)
        {
            throw new DamagedLinkedListEx(this);
        }
    }
}

// ------------------ getters -----------------------

LinkedListNode *LinkedListNode::getNext()
{
    return this->next;
}

LinkedListNode *LinkedListNode::getPrevious()
{
    return this->previous;
}

LinkedListNode::Header* LinkedListNode::getHeader()
{
    return  this->extern_header;
}

} //end of DataJuggler namespace
