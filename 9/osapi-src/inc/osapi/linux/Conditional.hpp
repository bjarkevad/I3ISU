#ifndef OSAPI_LINUX_COND_HPP
#define OSAPI_LINUX_COND_HPP

#include <pthread.h>
#include <time.h>
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
    pthread_condattr_t  condattr_;
    pthread_cond_t      cond_;
  };
}



#endif
