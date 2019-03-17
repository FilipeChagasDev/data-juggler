#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include "string.hpp"

namespace DataJuggler {

class Exception
{
    public:
        unsigned long long code;
        string name;
        string description;
        Exception(unsigned long long code, string name, string description);
};


class InvalidArgsEx : public Exception
{
    public:
     string function_name;
     string param_name;
     InvalidArgsEx(string function_name, string param_name);
     static const unsigned long long defaultCode = 5267;
};


} //end of DataJuggler namespace


#endif // EXCEPTION_HPP
