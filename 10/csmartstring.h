#ifndef CSMARTSTRING_H
#define CSMARTSTRING_H

#include <iostream>

class CSmartString
{
public:
    CSmartString(std::string* str);
    ~CSmartString();
    std::string* get();
    std::string* operator->();
    std::string& operator*();
    CSmartString(const CSmartString& other);
    void operator=(const CSmartString& other);

private:
    std::string* str_;
    unsigned int* counter_;
};
#endif // CSMARTSTRING_H
