//Hello 
#include "MsgQueue.h"


MsgQueue::MsgQueue(size_t maxSize_){
    maxSize = maxSize_;
    pthread_mutex_init(&editing_m, 0);
   //cout << "MSGQUEUE OPRETTET" << endl; 
}

void MsgQueue::send(unsigned int id, Message* msg){
   
  pthread_mutex_lock(&editing_m);
  
    //Vent til der er plads i vectoren
    while(numMsg>=maxSize){
      pthread_cond_wait(&freeSpace_c, &editing_m); 
    }
    
    item newItem;
    newItem.msg_ = msg;
    newItem.id_ = id; 
    
    Queue.push(newItem);
    numMsg++;
    
    //opvæk evt. ventende receiver
    pthread_cond_signal(&newItem_c);
    
    std::cout << "ID: " << id << " numMsg: " << numMsg << std::endl;
    pthread_mutex_unlock(&editing_m);
}

Message* MsgQueue::receive(unsigned int &id){
 
  pthread_mutex_lock(&editing_m);
  //Vent indtil der er nogle data tilgængelig:
  while(numMsg<=0){
      pthread_cond_wait(&newItem_c, &editing_m); 
  }
  
  item resultItem = Queue.front(); 
  
  Message* result_msg = resultItem.msg_;
  id = resultItem.id_;
  
  Queue.pop();
  numMsg--;
  
  pthread_cond_signal(&freeSpace_c);
  
  std::cout << "Størrelsen af Queue: " << numMsg << std::endl;
  
  pthread_mutex_unlock(&editing_m);
  
  return result_msg;
  
}

 MsgQueue::~MsgQueue(){
   
} 


