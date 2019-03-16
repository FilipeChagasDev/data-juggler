#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include "string.hpp"

namespace DataJuggler {

class Exception
{
    public:
        unsigned long hash;
        String name;
        String description;

        Exception(); //TODO
        ~Exception(); //TODO
};


} //end of DataJuggler namespace


#endif // EXCEPTION_HPP
