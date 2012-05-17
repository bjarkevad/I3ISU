#ifndef OSAPI_LINUX_THREAD_HPP
#define OSAPI_LINUX_THREAD_HPP

#include<pthread.h>
#include<string>

#include <osapi/Completion.hpp>


namespace osapi
{  
  class Thread
  {
  public:
    enum ThreadPriority
    {
      PRIORITY_LOW = 15,
      PRIORITY_BELOW_NORMAL = 30,
      PRIORITY_NORMAL = 45,
      PRIORITY_ABOVE_NORMAL = 60,
      PRIORITY_HIGH = 75
    };

    Thread(Thread::ThreadPriority p = PRIORITY_NORMAL, const std::string& name="");
    virtual ~Thread();
    void start();
    void setPriority(Thread::ThreadPriority p);
    Thread::ThreadPriority getPriority() const;
    std::string getName() const;

    void join();

  protected:
    virtual void run() = 0;

  private:
    ThreadPriority  priority_;
    std::string     name_;
    pthread_t       threadId_;
		pthread_attr_t  attr_;
    Completion      threadDone_;
    static void* threadMapper(void* p);
  };

}

#endif
