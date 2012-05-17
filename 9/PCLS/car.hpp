#include <osapi/MsgQueue.hpp>
#include <osapi/Thread.hpp>
#include <osapi/Utility.hpp>

#include "message.hpp"

class Car : public osapi::Thread {

	public:
		Car();
		~Car();
		void run();
		osapi::MsgQueue _msgQueue;

		Car& operator= (const Car&);

		void setMqs(osapi::MsgQueue &entryGuard_,
				osapi::MsgQueue &exitGuard_) 
		{ 
						entryMq = &entryGuard_; 
						exitMq = &exitGuard_;
		}

	private:
		bool running_;
		bool parked_;
		unsigned int id_;
		void MessageHandler(unsigned long _id, osapi::Message *_msg);
		osapi::MsgQueue *entryMq, *exitMq; 
};

//Implementation
Car::Car() : running_(false), 
	_msgQueue(2)
{

}

Car::~Car() {
	running_ = false;
}

void Car::run() {

	running_ = true;

	while(running_) {

		if(!parked_) {
			ReqMsg msgToSend(&_msgQueue);
			entryMq->send(ID_CAR_ENTRY_REQ, &msgToSend); 
			
			unsigned long id;
			osapi::Message* receivedMsg;
			receivedMsg = _msgQueue.receive(id);
			
			MessageHandler(id, receivedMsg); 

			//If still not parked, sleep and try again
			if(!parked_)
				osapi::sleep(1000);
			
			//Stay in for a while..
			if(parked_)
				osapi::sleep(10000);
		}
		
		else {
			ReqMsg msgToSend(&_msgQueue);
			exitMq->send(ID_CAR_EXIT_REQ, &msgToSend); 
			
			unsigned long id;
			osapi::Message* receivedMsg;
			receivedMsg = _msgQueue.receive(id);
			
			MessageHandler(id, receivedMsg); 

		}
	}
}

void Car::MessageHandler(unsigned long _id, osapi::Message *_msg) {

	switch(_id) {

		//ID_GUARD_ENTRY_CFM
		case(1) :
		{
			CfmMsg* receivedMsg;
			receivedMsg = static_cast<CfmMsg*>(_msg);

			if(receivedMsg->result_) {
				parked_ = true;
				std::cout << "Car entered.." << std::endl;
			}

			else 
				std::cout << "Car didn't enter.." << std::endl;


			break;
		}
		
		//ID_GUARD_EXIT_CFM
		case(3) : 
		{
			CfmMsg* receivedMsg;
			receivedMsg = static_cast<CfmMsg*>(_msg);
			
			if(receivedMsg->result_ && parked_) {
				parked_ = false;
				running_ = false;
				std::cout << "Car exited.." << std::endl;
			}

			break;
		}
		
		default :
			std::cout << "(CAR): Wrong message ID received.." 
								<< (unsigned long) _id << std::endl;
			break;
	}
}
