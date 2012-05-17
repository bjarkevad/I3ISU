#include "msgqueue.hpp"

//Number of cars
#define CARS 10 
//Number of parking spots
#define SPOTS 5

using namespace std;

int freeSpots = SPOTS;

MsgQueue entryMq,
	exitMq,
	carMq[CARS];

//Mutex to help do clean printing
pthread_mutex_t coutMutex;

void* car_func(void* _arg) {
	
	int carId = *(int*)_arg;
	bool parked = false;
	CfmMsg receivedMsg; 
	ReqMsg sentMsg;
	ID car_id;

	sentMsg.carId_ = carId;
	entryMq.send(ID_CAR_ENTRY_REQ, &sentMsg);


	while(1) {
	
		receivedMsg = static_cast<CfmMsg*>(carMq[carId].receive(car_id));

		if(receivedMsg.result_ && car_id == ID_GUARD_ENTRY_CFM && !parked) {

			pthread_mutex_lock(&coutMutex);	
			cout << "Car entered #" << carId << " with received id: " << car_id << endl;
			pthread_mutex_unlock(&coutMutex);	

			parked = true;

			sleep(5);
		}	
	
		if(parked) {

			exitMq.send(ID_CAR_EXIT_REQ, &sentMsg);
	
			receivedMsg = static_cast<CfmMsg*>(carMq[carId].receive(car_id));
		
			if(receivedMsg.result_ && car_id == ID_GUARD_EXIT_CFM) {  
				pthread_mutex_lock(&coutMutex);	
				cout << "Car exited #" << carId << " with received id: " << car_id <<  endl;
				pthread_mutex_unlock(&coutMutex);
				parked = false;
				pthread_exit(NULL);
cout << "BOOOOO" << endl;
			}
		}
	}
};

void* entry_func(void* _arg) {

	ReqMsg entryReceivedMsg;
	CfmMsg entrySentMsg;		
	ID entry_id;

	while(1) {
		// Only receive if there is at least one free spot	
		while(freeSpots > 0) {
			entryReceivedMsg = *static_cast<ReqMsg*>(entryMq.receive(entry_id));

			if(entry_id == ID_CAR_ENTRY_REQ) {
				
				entrySentMsg.result_ = true;
				
				carMq[entryReceivedMsg.carId_].send(ID_GUARD_ENTRY_CFM, &entrySentMsg);

				freeSpots--;

				pthread_mutex_lock(&coutMutex);	 				
				cout << "Car with ID " << entryReceivedMsg.carId_
					<< " requested access, there are now: "
					<< freeSpots << " free spots left.. " << endl;
				pthread_mutex_unlock(&coutMutex);

				//Give the car some time to enter
				sleep(1);
			}
		}
	}
};

void* exit_func(void* _arg) {

	ReqMsg exitReceivedMsg; 
	ID exit_id;
	CfmMsg exitSentMsg;


	while(1) {
		// Only receive if there is at least one free spot	
		exitReceivedMsg = *static_cast<ReqMsg*>(exitMq.receive(exit_id));

		if(exit_id == ID_CAR_EXIT_REQ) {
					
			exitSentMsg.result_ = true;
			carMq[exitReceivedMsg.carId_].send(ID_GUARD_EXIT_CFM, &exitSentMsg);
			freeSpots++;

			pthread_mutex_lock(&coutMutex);	 				
			cout << "Car with ID " << exitReceivedMsg.carId_
				<< " requested permission to leave, there are now: "
				<< freeSpots << " free spots left.. " << endl;
			pthread_mutex_unlock(&coutMutex);
			//Give the car some time to exit
			sleep(1);
		}
	}
};

int main(void) {

	pthread_t car_t[CARS],
		entry_t,
		exit_t;

	pthread_mutex_init(&coutMutex, NULL);	

	int carIdArr[CARS];

	for(int i = 0; i < CARS; i++) {
		carIdArr[i] = i;
		pthread_create(&car_t[i], NULL, &car_func, (void*)&carIdArr[i]);
	}

	pthread_create(&entry_t, NULL, &entry_func, NULL);
	pthread_create(&exit_t, NULL, &exit_func, NULL);

	for(int i = 0; i < CARS; i++)
		pthread_join(car_t[i],NULL);


}
