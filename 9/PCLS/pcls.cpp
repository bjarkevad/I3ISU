#include <iostream>
#include <osapi/Thread.hpp>

#include "guard.hpp"
#include "car.hpp"

#define NUMOFCARS 10

using namespace std;

int main(void) {

	Guard exitGuard,
				entryGuard;
	Car car[NUMOFCARS];

	entryGuard.start();
	exitGuard.start();

	for(int i = 0; i < NUMOFCARS; i++) {
		car[i].setMqs(entryGuard._msgQueue, exitGuard._msgQueue);
		car[i].start();
	}	

	while(1){}
}
