#ifndef LINEARNODE_H
#define LINEARNODE_H

namespace DataJuggler {

class LinearNode
{
    public:
        class Header
        {
            public:
                unsigned long counter;
                LinearNode *first;
                LinearNode *last;
        };

    protected:
        LinearNode::Header *extern_header;
        LinearNode *next;
        LinearNode *previous;

    public:
        LinearNode(LinearNode::Header *extern_header); //default constructor (header from pointer)
        LinearNode(LinearNode::Header &extern_header); //default constructor (header from ref)

        virtual ~LinearNode(); //TODO destructor

        virtual void CloneFrom(LinearNode *to_copy); //copy another LinearNode (object from pointer)
        virtual void CloneFrom(LinearNode &to_copy); //copy another LinearNode (object from reference)

        void insertAfter(LinearNode *to_insert);
        void insertBefore(LinearNode *to_insert); //TODO
        void moveToAfterOf(LinearNode *ref_node); //TODO
        void moveToBeforeOf(LinearNode *ref_node); //TODO
        void remove(); //TODO
};

} //end of DataJuggler namespace
#endif // LINEARNODE_H
