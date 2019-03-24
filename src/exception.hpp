#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include "string.hpp"

namespace DataJuggler {

/** This class represents an simple exception */
class Exception
{
    public:
        unsigned long long code;
        string name;
        string description;
        Exception(unsigned long long code, string name, string description);
};

/** This class represents an exception that is thrown a function receives an invalid argument */
class InvalidArgsEx : public Exception
{
    public:
     string function_name;
     string argument_info;
     InvalidArgsEx(string function_name, string argument_info);
     static const unsigned long long defaultCode = 5267;
};


} //end of DataJuggler namespace


#endif // EXCEPTION_HPP
