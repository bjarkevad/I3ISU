#include "msgqueue.hpp"

using namespace std;

MsgQueue mq(5);

void receiver_handler(Message* msg, ID id) {

	cout << "Handler called.. " << endl;
	switch(id) {
		
		case ID_3D_POINT: 

			cout << "ID_3D_POINT detected.." << endl;
			Point3D* p3d;
			p3d = dynamic_cast<Point3D*>(msg);
			cout << p3d->x << p3d->y << p3d->z << endl;
			break;

		case ID_2D_POINT:

			cout << "ID_2D_POINT detected.." << endl;
			Point2D* p2d;
			p2d = dynamic_cast<Point2D*>(msg);
			cout << p2d->x << p2d->y << endl;
			break;

		default:
			cout << "Error, ID unknown.." << endl;
			break;
	}
};

void* producer_func(void*) {

	cout << "3D Producer thread active.." << endl;
	ID myID = ID_3D_POINT;

	while(1) {

		for(int i = 0; i < 10; i++) {

			Point3D p3d1(i+1,i+2,i+3);
			cout << "Sending.. " << endl;	
			mq.send(myID, &p3d1);	
			sleep(1);
		}
	}
	//pthread_exit(NULL);
};

void *producer2d_func(void*) {

	cout << "2D Producer thread active.." << endl;
	ID myID = ID_2D_POINT;

	while(1) {

		for(int i = 0; i < 10; i++) {

			Point2D p2d1(i+1,i+2);
			cout << "Sending.. " << endl;	
			mq.send(myID, &p2d1);	
			sleep(1);
		}
	}
	//pthread_exit(NULL);
}

void* consumer_func(void*) {

	Message* receivedMsg;
	cout << "Consumer thread active.." << endl;

	for(int i = 0; i < 10; i++) {
		ID id;
		cout << "Receiving #" << i << endl;
		receivedMsg = mq.receive(id);
		receiver_handler(receivedMsg, id);
	}
	pthread_exit(NULL);
};




int main(void) {

	pthread_t consumer_t;
	pthread_t producer_t;
	pthread_t producer2d_t;

	pthread_create(&producer_t, NULL, &producer_func, NULL);
	pthread_create(&producer2d_t, NULL, &producer2d_func, NULL);
	
	cin.get();
	pthread_create(&consumer_t, NULL, &consumer_func, NULL);
	
	pthread_join(consumer_t, NULL);

	return 0;
}
