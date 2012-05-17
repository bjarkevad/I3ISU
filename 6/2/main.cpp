#include <iostream>
#include <pthread.h>

using namespace std;

#define NUMOFCARS 7 
#define NUMOFPARKINGSPOTS 5

pthread_mutex_t entryGuard = PTHREAD_MUTEX_INITIALIZER,
		exitGuard = PTHREAD_MUTEX_INITIALIZER,
		printGuard = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t gateOpen = PTHREAD_COND_INITIALIZER,
		entry = PTHREAD_COND_INITIALIZER,
		exit = PTHREAD_COND_INITIALIZER;

void car_enter(int _id);
void car_exit(int _id);

int carsWaiting = 0;
int _spots = NUMOFPARKINGSPOTS;

void *entryguard_function(void *_x) {

	while(1) {
		pthread_mutex_lock(&entryGuard);

		while(carsWaiting <= 0)
			pthread_cond_wait(&entry, &entryGuard);

		if(_spots > 0)
			pthread_cond_signal(&gateOpen);
		else {
			pthread_cond_wait(&exit, &entryGuard);
			pthread_cond_signal(&gateOpen);
		}

		pthread_mutex_unlock(&entryGuard);
	}
}

void *car_function(void* _id) {
	
	pthread_mutex_lock(&entryGuard);
	carsWaiting++;
	pthread_cond_signal(&entry);

	while(_spots <= 0) {
		pthread_cond_wait(&gateOpen, &entryGuard);
		cout << "waiting for gateOpen" << endl;
	}

	car_enter(*(int*) _id);
	carsWaiting--;
	pthread_mutex_unlock(&entryGuard);

	sleep(6);

	pthread_mutex_lock(&exitGuard);
	car_exit(*(int*) _id);
	pthread_cond_signal(&exit);
	pthread_mutex_unlock(&exitGuard);

	pthread_exit(NULL);
}

void car_enter(int _id) {

	_spots--;
	pthread_mutex_lock(&printGuard);
	cout << "Car #" << _id << " parked, there are now " << _spots << " spots left." << endl;
	pthread_mutex_unlock(&printGuard);
	sleep(1);
}

void car_exit(int _id) {

	_spots++;
	pthread_mutex_lock(&printGuard);
	cout << "Car #" << _id << " exiting, there are now " << _spots << " spots left." << endl;
	pthread_mutex_unlock(&printGuard);
	sleep(1);
}

int main(void) {

	pthread_t car[NUMOFCARS];
	pthread_t entryGuard_t;

	int idArray[NUMOFCARS];

	pthread_create(&entryGuard_t, NULL, &entryguard_function, NULL);

	for(int i = 0; i < NUMOFCARS; i++) {

		idArray[i] = i;
		cin.get();
		cout << "Car #" << i << " created" << endl;
		pthread_create(&car[i], NULL, &car_function, (void*)&idArray[i]); 
	}

	for(int i = 0; i < NUMOFCARS; i++) {

		pthread_join(car[i], NULL);
	}

	return 0;
}
