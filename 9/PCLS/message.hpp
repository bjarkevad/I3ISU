#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <osapi/Message.hpp>

struct ReqMsg : public osapi::Message {
	
	ReqMsg(osapi::MsgQueue* mq): carMq_ (mq){};
	osapi::MsgQueue* carMq_;
};

struct CfmMsg : public osapi::Message {
	
	CfmMsg(bool result = false): result_(result){};
	bool result_;
};

enum ID { 
	 ID_CAR_ENTRY_REQ = 0,
	 ID_GUARD_ENTRY_CFM = 1,
	 ID_CAR_EXIT_REQ = 2,
	 ID_GUARD_EXIT_CFM = 3
};

#endif
