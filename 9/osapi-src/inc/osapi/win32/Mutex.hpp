#ifndef OSAPI_WIN32_MUTEX_HPP
#define OSAPI_WIN32_MUTEX_HPP
#include <windows.h>
#include <osapi/Utility.hpp>

namespace osapi
{
  class Mutex : Notcopyable
  {
  public:
    Mutex();
    void lock();
    void unlock();
    CRITICAL_SECTION& nativeHandle();
    ~Mutex();
  private:
    CRITICAL_SECTION cs_;
  };
}



#endif
