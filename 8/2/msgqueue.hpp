#include <iostream>
#include <deque>
#include <pthread.h>

#include "message.hpp"

enum ID{ID_3D_POINT, ID_2D_POINT};

struct item {
	ID id_;
	Message* msg_;
};


class MsgQueue {

public:
	MsgQueue(int maxSize);
	~MsgQueue();

	void send(ID id, Message* msg = NULL);
	Message* receive(ID &id);

private:
	// A standard double-ended queue is used, the queue is filled with objects of type "item".
	// This type of queue is picked because objects can easily be popped from both front and back.
	std::deque<item>* mq;
	int maxSize,
		numMsg;
	pthread_mutex_t editMutex;
	pthread_cond_t notFull, 
			notEmpty;
	
};
