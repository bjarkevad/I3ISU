#ifndef MsgQueue_H
#define MsgQueue_H

#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <queue>
#include "Message.hpp"

struct item{
  int id_; 
  Message* msg_;
};

class MsgQueue
{
public:
   MsgQueue(size_t maxSize_);
   void send(unsigned int  id, Message* msg = NULL);
   Message* receive(unsigned int &id);
   ~MsgQueue(); 
private:
   std::queue<item> Queue;
   int numMsg;
   size_t maxSize;
   
   pthread_mutex_t editing_m;
   pthread_cond_t newItem_c;
   pthread_cond_t freeSpace_c; 
};



#endif
