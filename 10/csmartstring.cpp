#include "csmartstring.h"

CSmartString::CSmartString(std::string *str)
{
    //NOTE: Counter dynamically initialized in "real" constructor, other constructors copy this value so it can not cease to exist on class destructor
    str_= new std::string(*str);
    counter_ = new unsigned int(1);
}

CSmartString::CSmartString(const CSmartString &other)
{
    counter_ = other.counter_ ;
    str_ = other.str_;
    (*counter_)++;
}

void CSmartString::operator =(const CSmartString &other)
{
		(*counter_)--;

    counter_ = other.counter_ ;
    str_ = other.str_;
    (*counter_)++;
}

CSmartString::~CSmartString()
{
    if((*counter_) == 1) {
        delete str_;
        delete counter_;
    }
		else
    	(*counter_)--;
}

std::string *CSmartString::get()
{
    return str_;
}

std::string *CSmartString::operator ->()
{
    return str_;
}

std::string &CSmartString::operator *()
{
    return *str_;
}


