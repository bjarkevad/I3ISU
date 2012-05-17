#ifndef GUARD_HPP
#define GUARD_HPP

#include <osapi/MsgQueue.hpp>
#include <osapi/Thread.hpp>
#include <iostream>

#include "message.hpp"

#define PARKINGSPOTS 5 

class Guard : public osapi::Thread {

	public: 
		Guard();  
		~Guard();
		void run();
		static unsigned int freeSpots;
		osapi::MsgQueue _msgQueue;
	
	private:
		bool running_;
		void MessageHandler(unsigned long _id, osapi::Message* _msg) const;
};

//Implementation

unsigned int Guard::freeSpots = PARKINGSPOTS;

Guard::Guard() : osapi::Thread(PRIORITY_NORMAL) , running_(false), _msgQueue(5) {

}

Guard::~Guard() {
	running_ = false;
}

void Guard::run() {

	running_ = true;
	
	unsigned long id;
	osapi::Message* receivedMsg;

	while(running_) {
		receivedMsg =	_msgQueue.receive(id);
		MessageHandler(id, receivedMsg);
		osapi::sleep(1000);	
	}
}

void Guard::MessageHandler(unsigned long _id, osapi::Message* _msg) const {

	switch(_id) {

	//ID_CAR_ENTRY_REQ
	case(0) : {
		
		ReqMsg* receivedMsg;
		receivedMsg = static_cast<ReqMsg*>(_msg);

		if(freeSpots > 0) {
			CfmMsg msgToSend(true);
			receivedMsg->carMq_->send(ID_GUARD_ENTRY_CFM, &msgToSend);
			freeSpots--;
		}

		else {
			CfmMsg* msgToSend;
			msgToSend->result_ = false;
			receivedMsg->carMq_->send(ID_GUARD_ENTRY_CFM, msgToSend);
			std::cout << "Car not granted access.." << std::endl;
		}
			
		break;
	}	
  
	//ID_CAR_EXIT_REQ
	case(2) : {

		ReqMsg* receivedMsg;
		receivedMsg = static_cast<ReqMsg*>(_msg);

		CfmMsg* msgToSend;
		msgToSend->result_ = true;
		receivedMsg->carMq_->send(ID_GUARD_EXIT_CFM, msgToSend);
		freeSpots++;
		
		break;
	}

	default :
		std::cout << "(GUARD): Wrong message ID received.." << std::endl;
		break;

	}
}

#endif	
