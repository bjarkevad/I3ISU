//=========================================================================================
// A test program to test threads and their relative priorities
// Build this program and run it (don't forget to run with 'sudo'). Two threads will be
// started: a NormalPriorityThread and a VariablePriorityThread. They both count as fast as
// they can in their respective variables. A third thread, an OutputThread, will output and
// clear the variables every second.
//
// You can set the priority of the VariablePriorityThread to numbers 0 thru 4 (LOW thru HIGH
// priority).
// - When set lower than NORMAL (0 or 1), you should only see the NormalPriorityThread count.
// - When set to NORMAL (2), you should see both threads count
// - When set to higher than NORMAL (3 or 4), you should only see the VariablePriorityThread
//   count.
//
// If this is not the case, you have an epic fail in your thread class and must take this
// course again next year...or try to find the fail and correct it :)
//
//=========================================================================================
#include<iostream>

#include <osapi/Thread.hpp>
#include <osapi/Utility.hpp>

volatile unsigned int npCount = 0;
volatile unsigned int varCount=0;


class NormalPriorityThread : public osapi::Thread
{
public:
  NormalPriorityThread() : osapi::Thread(PRIORITY_NORMAL) {};
  void run()
  {
    for(;;) ++npCount;
  }
};

class VariablePriThread : public osapi::Thread
{
public:
  VariablePriThread() : osapi::Thread(PRIORITY_LOW) {};
  void run()
  {
    for(;;) ++varCount;
  }
};

class OutputThread : public osapi::Thread
{
public:
  OutputThread() : osapi::Thread(PRIORITY_NORMAL) {};
  void run()
  {
    while(true)
    {
      std::cout << "NP: " << npCount << " VP: " << varCount << std::endl;
      npCount = varCount = 0;
      osapi::sleep(1000);
    }
  }

};


int main()
{
	std::cin.get();

  int pri;

  NormalPriorityThread normalPriThread;
  VariablePriThread variablePriThread;
  OutputThread output;

  output.start();
  normalPriThread.start();
  variablePriThread.start();

 /*	while(true)
  {
    std::cin >> pri;
    switch(pri)
    {
      case 0:	variablePriThread.setPriority(osapi::Thread::PRIORITY_LOW);			break;
      case 1:	variablePriThread.setPriority(osapi::Thread::PRIORITY_BELOW_NORMAL); 	break;
      case 2:	variablePriThread.setPriority(osapi::Thread::PRIORITY_NORMAL); 		break;
      case 3:	variablePriThread.setPriority(osapi::Thread::PRIORITY_ABOVE_NORMAL); 	break;
      case 4:	variablePriThread.setPriority(osapi::Thread::PRIORITY_HIGH); 			break;
      default:	break;
    }
  }*/

	osapi::sleep(10000);
}
