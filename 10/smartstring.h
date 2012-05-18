#ifndef SMARTSTRING_H
#define SMARTSTRING_H

#include <iostream>

class SmartString
{
public:
    SmartString(std::string* str);
    ~SmartString();
    std::string* get();
    std::string* operator->();
    std::string& operator*();

private:
    SmartString(const SmartString& other){};
    void operator=(const SmartString& other){};

    std::string* str_;

};

#endif // SMARTSTRING_H
