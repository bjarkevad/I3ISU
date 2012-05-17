#ifndef OSAPI_WIN32_THREAD_HPP
#define OSAPI_WIN32_THREAD_HPP

#include<windows.h>
#include<string>

namespace osapi
{

  class Thread
  {
  public:
	// Thread priorities
	enum ThreadPriority{
      PRIORITY_LOW          = THREAD_PRIORITY_LOWEST,
      PRIORITY_BELOW_NORMAL = THREAD_PRIORITY_BELOW_NORMAL,
      PRIORITY_NORMAL       = THREAD_PRIORITY_NORMAL,
      PRIORITY_ABOVE_NORMAL = THREAD_PRIORITY_ABOVE_NORMAL,
      PRIORITY_HIGH         = THREAD_PRIORITY_HIGHEST,
	};

	Thread(ThreadPriority pri = Thread::PRIORITY_NORMAL, const std::string& name = "");
	~Thread();

	void start();
	void setPriority(ThreadPriority pri); 
	ThreadPriority getPriority() const;
    std::string getName() const;

    void join();
    
  protected:
	virtual void run() = 0;

  private:
	ThreadPriority priority_;
	std::string    name_;
	HANDLE         handle_;
	static DWORD WINAPI threadMapper(void* p) ;

  };
}

#endif