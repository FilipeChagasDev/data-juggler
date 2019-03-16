#include "linearnode.hpp"

namespace DataJuggler {

    // ---------- Constructors ------------

    LinearNode::LinearNode(LinearNode::Header *extern_header)
    {
        this->extern_header = extern_header;
        this->next = nullptr;
        this->previous = nullptr;
    }

    LinearNode::LinearNode(LinearNode::Header &extern_header)
    {
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
        bool im_the_first = (this->previous == nullptr);
        bool im_the_last = (this->next == nullptr);
        bool have_header = (this->extern_header != nullptr);

        //check for errors
        if(to_insert == nullptr)
        {
            throw; //TODO throws exception object here
        }

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

        to_insert->next = this->next;
        to_insert->previous = this;
        this->next = to_insert;

        if(!im_the_last) //true whether this is not the last
        {
            this->next->previous = to_insert;
        }
        else
        { //do it whether this is the last
            if(have_header) this->extern_header->last = to_insert;
        }

        if(have_header) this->extern_header++;
    }

} //end of DataJuggler namespace
