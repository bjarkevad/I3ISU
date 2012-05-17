#ifndef OSAPI_COND_HPP
#define OSAPI_COND_HPP

#include <osapi/Exceptions.hpp>

namespace osapi
{  
  class ConditionalError : public SystemError
  {
  public:
    ConditionalError()
      : SystemError("Some conditional error occurred!")
    {}
    
  };
}


#if defined(OS_WIN32)
#include "osapi/win32/Conditional.hpp"
#elif defined(OS_LINUX)
#include "osapi/linux/Conditional.hpp"
#endif


#endif
