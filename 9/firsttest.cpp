/*
 * =====================================================================================
 *
 *       Filename:  firsttest.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  26/04/12 12:56:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <iostream>
#include <osapi/Utility.hpp>
#include <osapi/Thread.hpp>
#include <osapi/Mutex.hpp>
#include <osapi/ScopedLock.hpp>
#include <osapi/Conditional.hpp>


using namespace std;
using namespace osapi;

osapi::Mutex mutex;
Conditional cond;

class myThread: public osapi::Thread {
	public:
		myThread(): osapi::Thread() {};
		void run() {
			int i = 0;
			while(i < 5) {
				cin.get();
				cout << "running like a motherfucker.." << endl;
				i++;
			}
		}
};

void* testFunc(void*) {
	while(1) {
		mutex.lock();
		cond.wait(mutex);
		cout << "testFunc" << endl;
		mutex.unlock();	
	}
}

void* testFunc2(void*) {
	while(1) {
		cond.signal();
	}
}

int main(void) {


	myThread test3;
	test3.start();
	return 0;
}
