#include "smartstring.h"

SmartString::SmartString(std::string *str)
{
    str_= new std::string(*str);
}

SmartString::~SmartString()
{
    delete str_;
}

std::string *SmartString::get()
{
    return str_;
}

std::string *SmartString::operator ->()
{
    return str_;
}

std::string &SmartString::operator *()
{
    return *str_;
}

