#ifndef OSAPI_MUTEX_HPP
#define OSAPI_MUTEX_HPP

#include <osapi/Exceptions.hpp>

namespace osapi
{  
  class MutexError : public SystemError
  {
  public:
    MutexError()
      : SystemError("Some mutex error occurred!")
    {}
    
  };
}


#if defined(OS_WIN32)
#include "osapi/win32/Mutex.hpp"
#elif defined(OS_LINUX)
#include "osapi/linux/Mutex.hpp"
#else
#error "No known OS defined"
#endif



#endif
