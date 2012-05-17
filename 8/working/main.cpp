//Hello 
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "Message.hpp"
#include "MsgQueue.h"

using namespace std; 

enum{
  ID_Point3D = 0, 
  ID_Point2D = 1
};

struct Point3D: public Message {
   Point3D(int x_,int y_,int z_):x(x_), y(y_), z(z_){};
   int x;
   int y; 
   int z; 
};

struct Point2D: public Message {
   Point2D(int x_,int y_):x(x_), y(y_){};
   int x;
   int y; 
};

void *senderFunction3D(void* arg);
void *senderFunction2D(void* arg);
void *receiverFunction(void* arg);

MsgQueue MQ(10); 

Point3D p_3D(1,2,3);
Point2D p_2D(4,5);

int main(){ 

pthread_t receiverThread;

int num3DThreads, num2DThreads;

cout << "Indtast antal 3D-sender tråde: " << endl;
cin >> num3DThreads; 

cout << "Indtast antal 2D-sender tråde: " << endl;
cin >> num2DThreads; 

pthread_t senderThread3D[num3DThreads];
pthread_t senderThread2D[num2DThreads];

int ID[num3DThreads];
for(int i = 0; i<num3DThreads; i++){
  ID[i]=i;
}


int k; 
for(k= 0; k<num3DThreads; k++){
	if(pthread_create(&senderThread3D[k], NULL, senderFunction3D,(void*)&ID[k])){
	   cout << "THREAD CREATION FAILED" << endl;
	   exit(EXIT_FAILURE);
	}
}

for(k= 0; k<num2DThreads; k++){
	if(pthread_create(&senderThread2D[k], NULL, senderFunction2D,(void*)&ID[k])){
	   cout << "THREAD CREATION FAILED" << endl;
	   exit(EXIT_FAILURE);
	}
}

if(pthread_create(&receiverThread, NULL, receiverFunction,(void*)&ID[0])){
   cout << "THREAD CREATION FAILED" << endl; 
   exit(EXIT_FAILURE); 
}

  
void *thread_result;
  
//Jointer tråde igen og slutter 
/*if(pthread_join(senderThread, &thread_result)){
   cout << "Join FAILED" << endl; 
   exit(EXIT_FAILURE); 
}*/

if(pthread_join(receiverThread, &thread_result)){
   cout << "Join FAILED" << endl; 
   exit(EXIT_FAILURE); 
}

  cout << "Tråde joined" << endl;
  exit(EXIT_SUCCESS);
}


void *senderFunction2D(void* arg){
    int *ID = (int*)arg;
    Point2D p_2D(*ID,*ID+1);
    
    while(1){
      MQ.send(ID_Point2D, &p_2D); 
    //sleep(1);   
    }
}


void *senderFunction3D(void* arg){
    int *ID = (int*)arg;
    Point3D p_3D(*ID,*ID+1,*ID+2);
    
    while(1){
      MQ.send(ID_Point3D, &p_3D); 
      //sleep(1);   
    }
  
}

void *receiverFunction(void* arg){
 Message* receivedMessage;
 unsigned int receivedID;
 Point2D* p2D_received;
 Point3D* p3D_received;
 while(1){
  
   receivedMessage = MQ.receive(receivedID);
  
   switch(receivedID){
    case ID_Point2D:
      p2D_received = dynamic_cast<Point2D*>(receivedMessage);
      cout << "FRA RECEIVERTRÅD: " << (*p2D_received).x << (*p2D_received).y << endl; 
      break; 
   
    case ID_Point3D:
      p3D_received = dynamic_cast<Point3D*>(receivedMessage);
      cout << "FRA RECEIVERTRÅD: " << (*p3D_received).x << (*p3D_received).y << (*p3D_received).z << endl; 
      break; 
    
    default:
      cout << "FRA RECEIVERTRÅD: Id'et blev ikke genkendt!" << endl;
      break;
  }
  
  
  
 
 }
}
