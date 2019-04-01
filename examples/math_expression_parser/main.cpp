#include <iostream>
#include <datajuggler.hpp>
//#include "../../datajuggler.hpp"
#include <string>

#define LOG( cmd )

using namespace std;

class ExpressionNode : public DataJuggler::BinaryTreeNode
{
public:
    ExpressionNode();
    char signal;
    virtual float getValue() = 0;
};

ExpressionNode::ExpressionNode() : DataJuggler::BinaryTreeNode ()
{
    this->signal = '+';
}

// --- ADDNode ----
class ADDNode : public ExpressionNode
{
public:
    virtual float getValue();
};

float ADDNode::getValue()
{
    float v = 0;
    float sigl = static_cast<ExpressionNode*>(this->left)->signal == '-' ? -1 : 1;
    float sigr = static_cast<ExpressionNode*>(this->right)->signal == '-' ? -1 : 1;

    if(this->left != nullptr)
    {
        v += static_cast<ExpressionNode*>(this->left)->getValue() * sigl;
    }

    if(this->right != nullptr)
    {
        v += static_cast<ExpressionNode*>(this->right)->getValue() * sigr;
    }

    return v;
}

// --- MULNode ----
class MULNode : public ExpressionNode
{
public:
    virtual float getValue();
};

float MULNode::getValue()
{
    float v = 1;
    float sigl = static_cast<ExpressionNode*>(this->left)->signal == '-' ? -1 : 1;
    float sigr = static_cast<ExpressionNode*>(this->right)->signal == '-' ? -1 : 1;

    if(this->left != nullptr) v *= static_cast<ExpressionNode*>(this->left)->getValue() * sigl;
    if(this->right != nullptr) v *= static_cast<ExpressionNode*>(this->right)->getValue() * sigr;
    return v;
}

// --- DIVNode ----
class DIVNode : public ExpressionNode
{
public:
    virtual float getValue();
};

float DIVNode::getValue()
{
    float v = 1;
    float sigl = static_cast<ExpressionNode*>(this->left)->signal == '-' ? -1 : 1;
    float sigr = static_cast<ExpressionNode*>(this->right)->signal == '-' ? -1 : 1;

    if(this->left != nullptr) v *= static_cast<ExpressionNode*>(this->left)->getValue() * sigl;
    if(this->right != nullptr) v /= static_cast<ExpressionNode*>(this->right)->getValue() * sigr;
    return v;
}

// --- CONSTNode ----
class CONSTNode : public ExpressionNode
{
public:
    float value;
    virtual float getValue();
};

float CONSTNode::getValue()
{
    return this->value;
}

// --------- Parsers ---------------

bool belong(char c, string set)
{
    for(int i = 0; i < set.length(); i++)
    {
        if(set[i] == c) return true;
    }
    return false;
}

bool is_number(char c)
{
    return c >= '0' && c <= '9';
}

string shifter(string str)
{
    // ------- shifting operators --------
    for(int i = 0; i < str.length(); i++)
    {
        if(!belong(str[i], "0123456789-+*/() \t"))
        {
            throw "undefined symbol";
        }
    }

    for(int i = 0; i < str.length(); i++)
    {
        if(belong(str[i],"\t ")) continue;
        if(is_number(str[i]) || belong(str[i], "-+(")) break;
        if(belong(str[i], "\*).")) throw "expression begin with operator";
    }

    // ----- middle chars -------
    for(int i = 0; i < str.length(); i++)
    {
        if(str[i] == ' ' || str[i] == '\t') continue;
        // --------- + -------
        if(str[i] == '+')
        {
            bool found_before = false;
            bool found_after = false;
            for(int j = i-1; j >= 0; j--)
            {
                if(belong(str[j], "\t ")) continue;
                if(is_number(str[j]) || belong(str[j], ")"))
                {
                    found_before = true;
                    break;
                }
                else break;
            }

            for(int j = i+1; j < str.length(); j++)
            {
                if(belong(str[j], "\t ")) continue;
                if(is_number(str[j]) || belong(str[j], "("))
                {
                    found_after = true;
                    break;
                }
                else if(belong(str[j], "/*)+")) throw "bad expression 0";
                else break;
            }

            if(found_before == false && found_after == false) throw  "bad expression 1";
            else if(found_before == false && found_after == true) str[i] = ' ';
            else if(found_before == true && found_after == false) throw "bad expression 2";
        }
        // ----------- - --------------
        else if(str[i] == '-')
        {
            bool found_before = false;
            bool found_after = false;
            for(int j = i-1; j >= 0; j--)
            {
                if(belong(str[j], "\t ")) continue;
                if(is_number(str[j]) || belong(str[j], ")"))
                {
                    found_before = true;
                    break;
                }
                else break;
            }

            for(int j = i+1; j < str.length(); j++)
            {
                if(belong(str[j], "\t ")) continue;
                if(is_number(str[j]) || belong(str[j], "("))
                {
                    found_after = true;
                    break;
                }
                else if(belong(str[j], "/*+)-")) throw "bad expression structure";
                else break;
            }

            if(found_before == false && found_after == false) throw  "bad expression 1";
            else if(found_before == false && found_after == true) str[i] = '@';
            else if(found_before == true && found_after == false) throw "bad expression 2";
        }
    }
    return str;
}

ExpressionNode *tree_parser(string str)
{
        ExpressionNode *resl, *resr, *res;
        LOG( cout << "parsing: " << str << endl );

        char signal = '+';
        for(int i = 0; i < str.length(); i++) //signal finding
        {
            if(belong(str[i],"\t ")) continue;
            if(str[i] == '@') signal = '-';
            break;
        }

        if(str.length() == 0)
        {
            throw "operator without operand";
        }


        // ---- Low Priority Operators ------
        for(int i = 0; i < str.length(); i++)
        {
                if(str[i] == '(')
                {
                        while(str[i] != ')')
                        {
                                i++;
                                if(i >= str.length()) throw "expected )";
                        }
                        i++;
                }

                if(str[i] == '-')
                {
                        string l = str.substr(0,i);
                        string r = "@" + str.substr(i+1,str.length()-i);
                        LOG(cout << "{" << l << "}" << "+" << "{" << r << "}" << endl);
                        resl = tree_parser(l);
                        resr = tree_parser(r);
                        res = new ADDNode();
                        res->insertLeft(resl);
                        res->insertRight(resr);
                        return res;
                }

                if(str[i] == '+')
                {
                        string l = str.substr(0,i);
                        string r = str.substr(i+1,str.length()-i);
                        LOG(cout << "{" << l << "}" << "+" << "{" << r << "}" << endl);
                        resl = tree_parser(l);
                        resr = tree_parser(r);
                        res = new ADDNode();
                        res->insertLeft(resl);
                        res->insertRight(resr);
                        return res;
                }
        }

        // ---- High Priority Operators ------
        for(int i = 0; i < str.length(); i++)
        {
                if(str[i] == '(')
                {
                        while(str[i] != ')')
                        {
                                i++;
                                if(i >= str.length()) throw "expected )";
                        }
                        i++;
                }

                if(str[i] == '/')
                {
                        string l = str.substr(0,i);
                        string r = str.substr(i+1,str.length()-i);
                        LOG(cout << "{" << l << "}" << "/" << "{" << r << "}" << endl);
                        resl = tree_parser(l);
                        resr = tree_parser(r);
                        res = new DIVNode();
                        res->insertLeft(resl);
                        res->insertRight(resr);
                        return res;
                }

                if(str[i] == '*')
                {
                        string l = str.substr(0,i);
                        string r = str.substr(i+1,str.length()-i);
                        LOG(cout << "{" << l << "}" << "*" << "{" << r << "}" << endl);
                        resl = tree_parser(l);
                        resr = tree_parser(r);
                        res = new MULNode();
                        res->insertLeft(resl);
                        res->insertRight(resr);
                        return res;
                }
        }

        // ---- () Scopes ------
        for(int i = 0; i < str.length(); i++)
        {
                if(str[i] == '(')
                {
                        for(int j = i; j < str.length(); j++)
                        {
                                if(str[j] == ')')
                                {
                                        string l = str.substr(i+1,(j-1)-i);
                                        LOG(cout << "{" << l << "}" << endl);
                                        res = tree_parser(l);
                                        res->signal = signal;
                                        return res;
                                }
                        }

                        throw "expected )";
                }
        }

        // -------- Numbers ---------
        float value = 0;
        bool algend = false, algfound = false, dotfound = false;
        float decimalfactor = 1;
        for(int i = 0; i < str.length(); i++)
        {
                if(str[i] == '@')
                {
                    if(algfound == true) throw "internal signal error";
                    signal = '-';
                    continue;
                }

                if(str[i] >= '0' && str[i] <= '9')
                {
                   algfound = true;
                   if(algend == true) throw "number without operator";

                   if(dotfound == false) value *= 10; //before dot
                   else decimalfactor *= 10; //after dot

                   value += (float)(str[i] - '0') / decimalfactor ;
                }
                else if(str[i] == '.')
                {
                    if(algfound == false) throw "dot without number";
                    if(algend == true) throw "dot without number and operator";
                    dotfound = true;
                }
                else
                {
                    if(algfound == true) algend = true;
                }
        }

        res = new CONSTNode();
        res->signal = signal;
        static_cast<CONSTNode*>(res)->value = value;
        return res;
}


int main()
{
    std::cout << "Math expression parser, by Filipe Chagas" << std::endl;
    init:
    try
    {
        std::cout << "type a expression: ";
        string str;
        std::getline(std::cin, str);
        str = shifter(str);
        std::cout << "shifted: " << str << std::endl;
        std::cout << ">> " << tree_parser(str)->getValue() << std::endl;
    }
    catch (const char *str)
    {
        std::cout << "issue: " << str << std::endl;
    }
    goto init;
    return 0;
}



/*
float static_parser(string str, bool allowempty = false)
{
        float result, resultl, resultr;
        cout << "parsing: " << str << endl;

        float signal = (str[0] == '@')? -1 : 1;

        if(str.length() == 0)
        {
                if(allowempty == true) return 0;
                else throw "operator without operand";
        }

        for(int i = 0; i < str.length(); i++)
        {
                if(str[i] == '(')
                {
                        while(str[i] != ')')
                        {
                                i++;
                                if(i >= str.length()) throw "expected )";
                        }
                        i++;
                }

                if(str[i] == '-')
                {
                        string l = str.substr(0,i);
                        string r = "@" + str.substr(i+1,str.length()-i);
                        cout << "{" << l << "}" << "+" << "{" << r << "}" << endl;
                        resultl = static_parser(l, true);
                        resultr = static_parser(r);
                        result = resultl + resultr;
                        cout << "solving: " << "{" << resultl << "}" << "+" << "{" << resultr << "}=" << result << endl;
                        return result;
                }

                if(str[i] == '+')
                {
                        string l = str.substr(0,i);
                        string r = str.substr(i+1,str.length()-i);
                        cout << "{" << l << "}" << "+" << "{" << r << "}" << endl;
                        resultl = static_parser(l, true);
                        resultr = static_parser(r);
                        result = resultl + resultr;
                        cout << "solving: " << "{" << resultl << "}" << "+" << "{" << resultr << "}=" << result << endl;
                        return result;
                }
        }

        for(int i = 0; i < str.length(); i++)
        {
                if(str[i] == '(')
                {
                        while(str[i] != ')')
                        {
                                i++;
                                if(i >= str.length()) throw "expected )";
                        }
                        i++;
                }

                if(str[i] == '/')
                {
                        string l = str.substr(0,i);
                        string r = str.substr(i+1,str.length()-i);
                        cout << "{" << l << "}" << "/" << "{" << r << "}" << endl;
                        resultl = static_parser(l);
                        resultr = static_parser(r);
                        result = resultl / resultr;
                        cout << "solving: " << "{" << resultl << "}" << "/" << "{" << resultr << "}=" << result << endl;
                        return result;
                }

                if(str[i] == '*')
                {
                        string l = str.substr(0,i);
                        string r = str.substr(i+1,str.length()-i);
                        cout << "{" << l << "}" << "*" << "{" << r << "}" << endl;
                        resultl = static_parser(l);
                        resultr = static_parser(r);
                        result = resultl * resultr;
                        cout << "solving: " << "{" << resultl << "}" << "*" << "{" << resultr << "}=" << result << endl;
                        return result;
                }
        }

        for(int i = 0; i < str.length(); i++)
        {
                if(str[i] == '(')
                {
                        for(int j = i; j < str.length(); j++)
                        {
                                if(str[j] == ')')
                                {
                                        string l = str.substr(i+1,(j-1)-i);
                                        cout << "{" << l << "}" << endl;
                                        result = static_parser(l);
                                        cout << "solving =" << result << endl;
                                        return result * signal;
                                }
                        }
                        throw "expected )";
                }
        }

        float value = 0;
        bool algend = false, algfound = false, dotfound = false;
        float decimalfactor = 1;
        float signalfactor = 1;
        for(int i = 0; i < str.length(); i++)
        {
                if(str[i] == '@')
                {
                    if(algfound == true) throw "internal signal error";
                    signalfactor = -1;
                }

                if(str[i] >= '0' && str[i] <= '9')
                {
                   algfound = true;
                   if(algend == true) throw "number without operator";

                   if(dotfound == false) value *= 10; //before dot
                   else decimalfactor *= 10; //after dot

                   value += (float)(str[i] - '0') / decimalfactor ;
                }
                else if(str[i] == '.')
                {
                    if(algfound == false) throw "dot without number";
                    if(algend == true) throw "dot without number and operator";
                    dotfound = true;
                }
                else
                {
                    if(algfound == true) algend = true;
                }
        }

        return value * signalfactor;
}
*/
