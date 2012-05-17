#include <unistd.h>
#include <errno.h>

#include <osapi/Thread.hpp>


namespace osapi
{


  Thread::~Thread()
  {
		try {
    join();
    pthread_join(threadId_, NULL);
    pthread_attr_destroy(&attr_);
		}
		catch(...) {}
  }

  void Thread::start()
  {

    if(getuid() == 0) // Check to see if we are root
    {        
      sched_param sched_p;
      if(pthread_attr_setschedpolicy(&attr_, SCHED_RR) != 0) throw ThreadError();					// Set RR scheduling (RT, timesliced)
      if(pthread_attr_setinheritsched(&attr_, PTHREAD_EXPLICIT_SCHED) != 0) throw ThreadError();	// Create thread with explicit (non-inherited) scheduling - setting priority will not work otherwise!
      sched_p.sched_priority = static_cast<int>(priority_);							// Set priority
      if(pthread_attr_setschedparam(&attr_, &sched_p) != 0) throw ThreadError();					// Use the priority        
        
      if(pthread_create(&threadId_, &attr_, threadMapper, this) != 0) throw ThreadError();
    }
    else
    {
      if(pthread_create(&threadId_, NULL, threadMapper, this) != 0) throw ThreadError();          
    }  
  }




  void Thread::join()
  {
    threadDone_.wait();
  }


  void* Thread::threadMapper(void* thread)
  {
    /* Something is missing here - Determine what! */
    pThis->threadDone_.signal();
    return NULL;
  }

}
