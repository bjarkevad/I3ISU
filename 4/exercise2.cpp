#include <iostream>
#include <pthread.h>
#include <stdlib.h>

using namespace std;

void *incrementer_function(void *arg);
void *reader_function(void *arg);

int shared;

int main() {
	pthread_t incrementer;
	pthread_t reader;
	void *thread_result;

	cout << "Creating threads.." << endl;

	pthread_create(&incrementer, NULL, incrementer_function, NULL); 
	pthread_create(&reader, NULL, reader_function, NULL);

	cout << "Waiting for threads.." << endl;

	pthread_join(incrementer, &thread_result);
	pthread_join(reader, &thread_result);

	return 0;
}

void *incrementer_function(void *arg) {
	for(int i = 0; i < 20; i++) {
		cout << "Incrementing shared to: " << ++shared << endl;
		sleep(1);
	}
	cout << "Incrementer thread terminates.." << endl;
	pthread_exit(NULL);
}

void *reader_function(void *arg) {
	sleep(1);
	for(int i = 0; i < 20; i++) {
		cout << "Reading shared: " << shared << endl;
		sleep(1);
	}
	cout << "Reader thread terminates.." << endl;
	pthread_exit(NULL);
}
	
