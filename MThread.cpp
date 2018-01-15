#include "MThread.h"
#include <iostream>

using namespace std;

void* worker(void* arg){
	MThread* threadObj = (MThread*)arg;
	threadObj->run();
	return nullptr;
}

void MThread::start(){
	pthread_create(&threadId,nullptr,worker,(void*)this);
}

void MThread::waitForThread(){
	pthread_join(threadId, nullptr);
}

MThread::~MThread(){
	if (threadId>0){
		//kills the thread if exist
		//pthread_cancel(threadId);
		printf("Thread was canceled\n");
	}
}

