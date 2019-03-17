#include "stringhash.hpp"

namespace DataJuggler {

/*
#define NAME_CHAR_SET_LENGTH 63

char name_char_set[] = {'_', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                             'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
                             'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                             'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
                             'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
*/


StringHashOverflowEx::StringHashOverflowEx(string guilty)
    : Exception(StringHashOverflowEx::defaultCode,
                "String Hash Overflow Exception",
                "the string passed as an argument to generate the hash is too long")
{
    this->guilty = guilty;
}

StringHashOutOfSetEx::StringHashOutOfSetEx(string guilty, string charset, unsigned long guilty_char_index)
    : Exception(StringHashOutOfSetEx::defaultCode,
                "String Hash Out Of Set Exception",
                "the string passed as an argument to generate the hash has a char not belonging to the charset")
{
    this->guilty = guilty;
    this->charset = charset;
    this->guilty_char_index = guilty_char_index;
}

string name_charset = "_0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

unsigned long long getStringHash(string charset, string str)
{
    unsigned long long hash = 0;

    for(unsigned long i = 0; i < str.length(); i++)
    {
        for(unsigned long j = 0; j < charset.length(); j++)
        {
            if(charset[j] == str[i]) //str[i] found in charset
            {

                hash += (charset.length() * i) + j; //calc

                if(hash > 0xFFFFFFFFFFFFFF00)
                {
                    throw new StringHashOverflowEx(str);
                }

                goto charfound; //stop sequential search
            }
        }

        //str[i] char not found in charset
        throw new StringHashOutOfSetEx(str, charset, i);

        charfound:;
    }

    return hash;
}


}//end of namespace
