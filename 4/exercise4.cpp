#include <pthread.h>
#include <iostream>
#include <stdlib.h>
#include "Vector.hpp"

using namespace std;

void *writer_function(void *arg);
Vector sharedVector;
void *thread_result;
int sleepTime = 0;

int main() {
	int numOfThreads = 0;
	cout << "Input number of writer threads: " << endl;
	cin >> numOfThreads;
	numOfThreads = (numOfThreads <= 100 && numOfThreads > 0 ? numOfThreads : 5); 
	cout << "Input sleep time in µ seconds: " << endl;
	cin >> sleepTime;
	pthread_t writer[numOfThreads];

	for(int i = 0; i < numOfThreads; i++) {
		cout << "Creating thread #" << i << endl;
		pthread_create(&writer[i], NULL, writer_function, (void *)&i);
		usleep(1); //Sleep for 1 µ second to make sure _id is updated in writer_function - NOT PREFERABLE!
	}

	for(int i = 0; i < numOfThreads; i++) {
		cout << "Waiting for thread #" << i << endl;
		pthread_join(writer[i], &thread_result);
	}

}

void *writer_function(void *arg) {
	int _id = *(int *) arg; 
	cout << "Writer from thread #" << _id << endl; 
	for(int i = 0; i < 20; i++) {
		if(!sharedVector.setAndTest(_id))
			cout << "Test returned false!" << endl;
		else 
			cout << "Test returned true!" << endl;
		usleep(sleepTime);
	}
	cout << "Exiting thread.." << endl;
	pthread_exit(NULL);
}
