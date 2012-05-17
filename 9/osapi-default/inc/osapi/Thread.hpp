#ifndef OSAPI_THREAD_HPP
#define OSAPI_THREAD_HPP

#include <osapi/Exceptions.hpp>

namespace osapi
{  
  class ThreadError : public SystemError
  {
  public:
    ThreadError()
      : SystemError("Some thread error occurred!")
    {}
    
  };
}


#if defined(OS_WIN32)
#include "osapi/win32/Thread.hpp"
#elif defined(OS_LINUX)
#include "osapi/linux/Thread.hpp"
#endif



#endif
