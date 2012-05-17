#ifndef OSAPI_WIN32_SEMAPHORE_HPP
#define OSAPI_WIN32_SEMAPHORE_HPP

#include <windows.h>
#include <osapi/Utility.hpp>

namespace osapi
{
  class Semaphore : Notcopyable
  {
  public:
    Semaphore(unsigned int initCount);
    void wait();
    void signal();
    ~Semaphore();
  private:
    HANDLE id_;
  };
}



#endif
