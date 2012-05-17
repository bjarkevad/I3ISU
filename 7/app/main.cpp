#include <iostream>
#include <pthread.h>
using namespace std;

#define NUMOFCARS 5

pthread_mutex_t entryGuard = PTHREAD_MUTEX_INITIALIZER,
		exitGuard = PTHREAD_MUTEX_INITIALIZER;

void *car_function(void* _id);
void car_enter(int _id);
void car_exit(int _id);

void *car_function(void* _id) {
	
	pthread_mutex_lock(&entryGuard);
	car_enter(*(int*)_id);
	pthread_mutex_unlock(&entryGuard);

	sleep(3);

	pthread_mutex_lock(&exitGuard);
	car_exit(*(int*)_id);	
	pthread_mutex_unlock(&exitGuard);
	
	pthread_exit(NULL);			
}

void car_enter(int _id) {

	cout <<"Car #" << _id << " entering" << endl; 
	sleep(1);

}

void car_exit(int _id) { 

	cout << "Car #" << _id << " exiting" << endl;
	sleep(1);
}



int main(void) {
	
	pthread_t car[NUMOFCARS];
	int idArray[NUMOFCARS];

	for(int i = 0; i < NUMOFCARS; i++) {

		idArray[i] = i;
		pthread_create(&car[i], NULL, &car_function, (void*)&idArray[i]); 
	}

	for(int i = 0; i < NUMOFCARS; i++) {

		pthread_join(car[i], NULL);
	}

	
	return 0;
}
