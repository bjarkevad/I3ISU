#include <iostream>
#include <pthread.h>
#include <stdlib.h>

using namespace std;

void *thread_function(void *arg);

int main() {
	int res;
	pthread_t thread1;
	pthread_t thread2;
	void *thread_result;
	cout << "Creating threads.." << endl;
	res = pthread_create(&thread1, NULL, thread_function, (void *)"1");
       /*	if(res != 0) {
		perror("Thread1 creation failed!");
		exit(EXIT_FAILURE);
	}*/
	res = pthread_create(&thread2, NULL, thread_function, (void *)"2");

	/*if(res != 0) {
		perror("Thread2 creation failed!");
		exit(EXIT_FAILURE);
	}*/
	cout << "Waiting for threads.." << endl;
	res = pthread_join(thread1, &thread_result);
	/*if(res != 0) {
		perror("Thread2 join failed!");
		exit(EXIT_FAILURE);
	}*/
	res = pthread_join(thread2, &thread_result);
	/*if(res != 0) {
		perror("Thread2 join failed!");
		exit(EXIT_FAILURE);
	}*/
	return 0;
}

void *thread_function(void *arg) {
	for(int i = 0; i < 20; i++) {	
	cout << "Hello #" << i << " from thread " << (char *)arg << endl; 
	sleep(1);
	}
	cout << "Thread " << (char *)arg << " terminates.." << endl; 
	pthread_exit(NULL);
}
