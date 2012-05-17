#include <osapi/Thread.hpp>

namespace osapi
{
  

  Thread::Thread(ThreadPriority priority, const std::string& name) 
    : priority_(priority),
      name_(name)
  {
  }


  Thread::~Thread()
  {
    try
    {
      join();
      CloseHandle(handle_);
    }
    catch(...)
    {
      // Have to ignore, may not throw exception in destructor
    }
  
  }

  void Thread::start()
  {
    handle_ = CreateThread(NULL, 0, threadMapper, this, 0, NULL);
    setPriority(priority_);
  }


  std::string Thread::getName() const
  {
    return name_;
  }


  void Thread::setPriority(ThreadPriority priority) 
  { 
    if(!SetThreadPriority(handle_, priority_)) throw ThreadError();
    priority_ = priority;
  }


  Thread::ThreadPriority Thread::getPriority() const
  {
    return priority_;
  }


  void Thread::join()
  {
    if(WaitForSingleObject(handle_, INFINITE) != 0) throw ThreadError();
  }


  DWORD WINAPI Thread::threadMapper(void* p) 
  { 
    static_cast<Thread*>(p)->run();
    return 0; 
  }

}
