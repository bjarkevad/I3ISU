#include "msgqueue.hpp"

using namespace std;

MsgQueue::MsgQueue(int _maxSize) {
	
	pthread_mutex_init(&editMutex, 0);
	pthread_cond_init(&notFull, 0);
	pthread_cond_init(&notEmpty, 0);

	cout << &editMutex << endl;
	cout << "msgqueue created .. " << endl;
	
	mq = new std::deque<item>;
	mq->resize(maxSize);
	maxSize = _maxSize;
	numMsg = 0;
}

MsgQueue::~MsgQueue() {

	delete mq;
}

void MsgQueue::send(ID id, Message* msg) {

	pthread_mutex_lock(&editMutex);

	while(numMsg == maxSize) {
		cout << "Queue full.. Waiting..." << endl;
		pthread_cond_wait(&notFull, &editMutex);
	}
	
	item tempItem;
	tempItem.id_ = id;
	tempItem.msg_ = msg;			
	
	mq->push_back(tempItem);
	++numMsg;	
	pthread_cond_signal(&notEmpty);
	
	pthread_mutex_unlock(&editMutex);
}

Message* MsgQueue::receive(ID &id) {

	pthread_mutex_lock(&editMutex);

	while(numMsg == 0)
		pthread_cond_wait(&notEmpty, &editMutex);

	item tempItem = mq->front();
	
	Message* tempMsg = tempItem.msg_;		
	id = tempItem.id_;

	mq->pop_front();
	numMsg--;
	pthread_cond_signal(&notFull);	
	pthread_mutex_unlock(&editMutex);
	
	return tempMsg;	
}
