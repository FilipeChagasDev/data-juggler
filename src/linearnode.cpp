#include "linearnode.hpp"

namespace DataJuggler {

DamagedLinearEx::DamagedLinearEx(LinearNode *node_where_throwed)
    :Exception(DamagedLinearEx::defaultCode, "Damaged Linear Exception",
               "A fault in the linear list structure was detected. Analyze the source code of the LinearNode class or its subclass.")
{
    this->node_where_throwed = node_where_throwed;
}

// ---------- Constructors ------------

LinearNode::LinearNode(LinearNode::Header *extern_header)
{
    if(extern_header != nullptr)
    {
        if(extern_header->first == nullptr && extern_header->last == nullptr)
        {
            extern_header->first = this;
            extern_header->last = this;
        }
    }

    this->extern_header = extern_header;
    this->next = nullptr;
    this->previous = nullptr;
}

LinearNode::LinearNode(LinearNode::Header &extern_header)
{
    if(extern_header.first == nullptr && extern_header.last == nullptr)
    {
        extern_header.first = this;
        extern_header.last = this;
    }

    this->extern_header = &extern_header;
    this->next = nullptr;
    this->previous = nullptr;
}

// ------------ Destructors -------------

LinearNode::~LinearNode()
{
    this->remove();
}

// ------------- Cloners -----------------

void LinearNode::CloneFrom(LinearNode *to_copy)
{
    this->extern_header = to_copy->extern_header;
    this->next = to_copy->next;
    this->previous = to_copy->previous;
}

void LinearNode::CloneFrom(LinearNode &to_copy)
{
    this->extern_header = to_copy.extern_header;
    this->next = to_copy.next;
    this->previous = to_copy.previous;
}

// ------------- Inserters ---------------

void LinearNode::insertAfter(LinearNode *to_insert)
{
    bool im_the_last = (this->next == nullptr);
    bool have_header = (this->extern_header != nullptr);

    //check for errors
    if(to_insert == nullptr)
    {
        throw new InvalidArgsEx("LinearNode::insertAfter", "LinearNode *to_insert");
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


void LinearNode::insertBefore(LinearNode *to_insert)
{
    bool im_the_first = (this->previous == nullptr);
    bool have_header = (this->extern_header != nullptr);

    //check for errors
    if(to_insert == nullptr)
    {
        throw new InvalidArgsEx("LinearNode::insertAfter", "LinearNode *to_insert");
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

void LinearNode::remove()
{
    bool im_the_first = (this->previous == nullptr);
    bool im_the_last = (this->next == nullptr);
    bool have_header = (this->extern_header != nullptr);

    //check for errors
    if(have_header)
    {
        if(im_the_first && this->extern_header->first != this)
        {
            throw; //TODO throws exception object here
        }

        if(im_the_last && this->extern_header->last != this)
        {
            throw; //TODO throws exception object here
        }
    }

    //lets go to what matters...
    LinearNode *my_next = this->next;
    LinearNode *my_previous = this->previous;

    if(!im_the_first) my_previous->next = my_next; //do it whether this is not the first
    else if(have_header) this->extern_header->first = my_next; //do it whether this is the first

    if(!im_the_last) my_next->previous = my_previous; //do it whether this is not the last
    else if(have_header) this->extern_header->last = my_previous; //do it whether this is the last

    this->next = nullptr;
    this->previous = nullptr;
    if(have_header) this->extern_header->counter--;
}

void LinearNode::moveToAfterOf(LinearNode *ref_node)
{
    this->remove();
    ref_node->insertAfter(this);
}

void LinearNode::moveToBeforeOf(LinearNode *ref_node)
{
    this->remove();
    ref_node->insertBefore(this);
}

void LinearNode::checkIntegrity()
{
    bool im_the_first = (this->previous == nullptr);
    bool im_the_last = (this->next == nullptr);
    bool have_header = (this->extern_header != nullptr);

    if(have_header)
    {
        if(im_the_first && this->extern_header->first != this)
        {
            throw new DamagedLinearEx(this);
        }

        if(im_the_last && this->extern_header->last != this)
        {
            throw new DamagedLinearEx(this);
        }
    }
}

// ------------------ getters -----------------------

LinearNode *LinearNode::getNext()
{
    return this->next;
}

LinearNode *LinearNode::getPrevious()
{
    return this->previous;
}

} //end of DataJuggler namespace
