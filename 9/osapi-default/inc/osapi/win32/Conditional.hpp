#ifndef OSAPI_WIN32_COND_HPP
#define OSAPI_WIN32_COND_HPP

#include <windows.h>
#include <osapi/Utility.hpp>
#include <osapi/Mutex.hpp>

namespace osapi
{
  class Conditional : Notcopyable
  {
  public:
    enum Awoken {
      SIGNALED,
      TIMEDOUT
    };
      
    Conditional();
    void signal();
    void broadcast();
    void wait(Mutex& mut);
    Awoken waitTimed(Mutex& mut, unsigned long timeout);
    ~Conditional();
  private:
    CONDITION_VARIABLE   cond_;
  };
}



#endif
