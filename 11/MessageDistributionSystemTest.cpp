#include <osapi/Log.hpp>
#include <osapi/Timer.hpp>
#include <osapi/Message.hpp>
#include <osapi/Thread.hpp>
#include <osapi/MsgQueue.hpp>

/**
 * It is presumed that you make your MessageDistributionSystem
 * in separate files. One for the hpp file and one for the cpp file.
 * Do yourselves a favor and make a makefile.
 */
#include "MessageDistributionSystem.hpp"


class MessageHandler : public osapi::Thread
{
public:
  MessageHandler(unsigned long count, unsigned long stopId)
    : mq_(count), running_(true), stopId_(stopId) {}
  
  osapi::MsgQueue* getMsgQueue()
  {
    return &mq_;
  }
  
  void stop()
  {
    mq_.send(stopId_);
  }
  
protected:  
  void run()
  {
    preMsgHandler();
    while(running_)
    {
      unsigned long id;
      osapi::Message* m = mq_.receive(id);
      if(id == stopId_)
        running_ = false;
      handleMsg(m, id);
      delete m;
    }
  }

  virtual void preMsgHandler() {}
  virtual void handleMsg(osapi::Message*& msg, unsigned long id) = 0;
  
private:
  osapi::MsgQueue   mq_;
  unsigned long     stopId_;
  bool              running_;
};


/** Global message Hello
 */
struct HelloMsg : public osapi::Message
{
  std::string data_;
};

  


/**
 * class Subscriber
 */
class Subscriber : public MessageHandler
{
public:
  enum { MAX_MSG_COUNT = 10 };
  Subscriber(unsigned int id = 1)
    :  MessageHandler(MAX_MSG_COUNT, ID_TERMINATE), id_(id), 
			 subHelp_("SUBS", getMsgQueue(), ID_HELLO)
					//We're subscribing to "SUBS" with our own message queues, and expecting messages 					
					////of type "ID_HELLO"
  {
  }
  
protected:
  // The subscription it self is missing and os is the unsubscription - Where will you put these?
	void preMsgHandler() 
	{
		//Used if no SubscribtionHelper is used
		//MessageDistributionSystem::getInstance().subscribe("SUBS", getMsgQueue(), id_);
	}

  virtual void handleMsg(osapi::Message*& msg, unsigned long id)
  {
    switch(id)
    {
      case ID_HELLO:
        OSAPI_LOG_DBG("S(" << id_ << ") The hello message contained: '" << static_cast<HelloMsg*>(msg)->data_ << "'");
        break;
        
      case ID_TERMINATE:
        OSAPI_LOG_DBG("S(" << id_ << ") Got terminate signal");
        break;
    }
    
  }
  
private:
  enum {
    ID_TERMINATE,
    ID_HELLO 
  };
  unsigned int id_;
	SubscriberHelper subHelp_;
};


/**
 * class Publisher
 */
class Publisher : public MessageHandler
{
public:
  enum { MAX_MSG_COUNT = 10 };
  Publisher()
    :  MessageHandler(MAX_MSG_COUNT, ID_TERMINATE)
  {
  }

protected:
  // The subscription it self is missing and os is the unsubscription - Where will you put these?
  enum { NOTIFY_TIMEOUT = 1000 
  };
  
  virtual void preMsgHandler()
  {
    timer_ = osapi::createNewTimer(getMsgQueue(), ID_NOTIFY);
    timer_->arm(NOTIFY_TIMEOUT); // Timeout in 1sec
  }
  
  virtual void handleMsg(osapi::Message*& msg, unsigned long id)
  {
    switch(id)
    {
      case ID_NOTIFY:
        handleIdNotify();
        break;
        
      case ID_TERMINATE:
        delete timer_;
        break;
    }
    
  }
  
private:
  enum {
    ID_TERMINATE,
    ID_NOTIFY 
  };

  void handleIdNotify()
  {
    // Send notification...
    OSAPI_LOG_DBG("Sending notification...");
		HelloMsg* msg = new HelloMsg;
		msg->data_ = "Hello world!";
   	MessageDistributionSystem::getInstance().notify<HelloMsg>("SUBS", msg); 
    // When done we need to rearm the timer
    timer_->reArm();
  }
  
  osapi::ITimerId*  timer_;

};



int main(int argc, char* argv[])
{
  OSAPI_LOG_INF("Application starting up...");

  Publisher p;

  /*Subscriber s1(1), s2(2);
  s1.start();
  s2.start();*/
  p.start();

	Subscriber subs[100];
	for( int i = 0 ; i< 100 ; i++ )
	{
		subs[i].start();
	}
	
 /* s1.join();
  s2.join();*/
  p.join();
}
