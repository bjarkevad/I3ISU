#include <errno.h>
#include <osapi/Conditional.hpp>

namespace osapi
{
  Conditional::Conditional()
  {
    /* Deliberately empty! */
    /* Note that you have to setup the conditional variable to
       use the monotonic clock. Otherwise the function waitTimed()
       will not work as expected. */
  }

  Conditional::Awoken Conditional::waitTimed(Mutex& mut, unsigned long timeout)
  {
    struct timespec ts;
  
    // Get monotonic clock - current time
    clock_gettime(CLOCK_MONOTONIC, &ts);

    // Calculate new absolute time by getting current monotonic time and offsetting it
    size_t secs = timeout/1000;
    size_t msecs = timeout - secs*1000;

    ts.tv_sec += secs;
    ts.tv_nsec += msecs*1000000;
    size_t overflow = ts.tv_nsec/1000000000;
  
    if(overflow)
    {
      ts.tv_sec += overflow;
      ts.tv_nsec -= overflow*1000000000;
    }  

    int res = pthread_cond_timedwait(&cond_, &mut.nativeHandle(), &ts);
    
    switch(res)
    {
      case ETIMEDOUT:
        return TIMEDOUT;
        break;
        
      case 0:
        return SIGNALED;
        break;

      default:
        throw ConditionalError();
    }
  }


}
