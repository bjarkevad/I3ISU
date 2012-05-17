#ifndef OSAPI_LINUX_MUTEX_HPP
#define OSAPI_LINUX_MUTEX_HPP

#include <pthread.h>
#include <osapi/Utility.hpp>

namespace osapi {
  class Mutex : Notcopyable {
    public:
      Mutex();
      void lock();
      void unlock();
    pthread_mutex_t& nativeHandle();
      ~Mutex();
      
    private:
      pthread_mutex_t mut_;
  };
}

#endif
