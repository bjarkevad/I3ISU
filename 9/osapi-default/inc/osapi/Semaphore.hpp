#ifndef OSAPI_SEMAPHORE_HPP
#define OSAPI_SEMAPHORE_HPP

#include <osapi/Exceptions.hpp>

namespace osapi
{  
  class SemaphoreError : public SystemError
  {
  public:
    SemaphoreError()
      : SystemError("Some semaphore error occurred!")
    {}
    
  };
}


#if defined(OS_WIN32)
#include "osapi/win32/Semaphore.hpp"
#elif defined(OS_LINUX)
#include "osapi/linux/Semaphore.hpp"
#else
#error "No known OS defined"
#endif



#endif
