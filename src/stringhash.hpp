#ifndef NAMEHASH_HPP
#define NAMEHASH_HPP

#include "string.hpp"
#include "exception.hpp"

namespace DataJuggler {

class StringHashOverflowEx : Exception
{
    public:
        string guilty;
        StringHashOverflowEx(string guilty);
        static const unsigned long long defaultCode = 12542;
};

class StringHashOutOfSetEx : Exception
{
    public:
        string guilty;
        string charset;
        unsigned long guilty_char_index;

        StringHashOutOfSetEx(string guilty, string charset, unsigned long guilty_char_index);
        static const unsigned long long defaultCode = 12599;
};

extern string name_charset;
unsigned long long getStringHash(string charset, string str);

}//end of namespace

#endif // NAMEHASH_HPP
