#include <iostream>
#include <deque>
#include <pthread.h>

class MsgQueue;

class Message {

public:
	virtual ~Message() {};
};

struct ReqMsg: public Message {

	ReqMsg(int carId = 0): carId_(carId){};
	//MsgQueue* mq_;
	int carId_;
};

struct CfmMsg: public Message {
	
	CfmMsg(bool result = false): result_(result){};
	bool result_;
};

enum ID { 
	 ID_CAR_ENTRY_REQ = 0,
	 ID_GUARD_ENTRY_CFM = 1,
	 ID_CAR_EXIT_REQ = 2,
	 ID_GUARD_EXIT_CFM = 3
};

struct item {
	ID id_;
	Message* msg_;
};

//--------------------------------------------

class MsgQueue {

public:
	MsgQueue(int maxSize = 10);
	~MsgQueue();

	void send(ID id, Message* msg = NULL);
	Message* receive(ID &id);
	void printSize();

private:
	std::deque<item>* mq;
	int maxSize,
		numMsg;
	pthread_mutex_t editMutex;
	pthread_cond_t notFull, 
			notEmpty;
	
};
