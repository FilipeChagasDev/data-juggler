#include "exception.hpp"
namespace DataJuggler{

Exception::Exception(unsigned long long code, string name, string description)
{
    this->code = code;
    this->name = name;
    this->description = description;
}

InvalidArgsEx::InvalidArgsEx(string function_name, string param_name)
    :Exception (InvalidArgsEx::defaultCode, "Invalid Arguments Exceptions", "A function that received an invalid argument threw this exception")
{
    this->function_name = function_name;
    this->argument_info = param_name;
}

}//end of namespace
