#include <osapi/Semaphore.hpp>

namespace osapi
{  
  const unsigned int MAX_COUNT=1024;
  
  Semaphore::Semaphore(unsigned int initCount)
    : 	id_(CreateSemaphore(0, initCount, MAX_COUNT, NULL))
  {
    if(!id_) throw SemaphoreError();
  }


  void Semaphore::wait()
  {
	if(WaitForSingleObject(id_, INFINITE) == WAIT_FAILED) throw SemaphoreError();
  }


  void Semaphore::signal()
  {
	if(ReleaseSemaphore(id_, 1, NULL) == 0) throw SemaphoreError();
  }


  Semaphore::~Semaphore()
  {
    CloseHandle(id_);
  }

}
