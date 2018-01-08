//
// Created by root on 1/1/18.
//

#ifndef NEWSSYSTEM_DISPATCHER_H
#define NEWSSYSTEM_DISPATCHER_H

#include <vector>
#include <string>
#include "ProducerQueue.h"
#include "SortedNewsQueue.h"
#include "MThread.h"

using namespace std;

class Dispatcher : public MThread {

    vector<ProducerQueue*>* producersQueues;
    SortedNewsQueue* sportQueue;
    SortedNewsQueue* weatherQueue;
    SortedNewsQueue* newsQueue;
    int producerDoneCounter;

    void readFromProducersQueues();
    void pushToSortedNewsQueue(string news);

public:

    Dispatcher(vector<ProducerQueue *>* producersQueues, SortedNewsQueue *sportQueue,
               SortedNewsQueue *weatherQueue, SortedNewsQueue *newsQueue);
    void run() override;
};


#endif //NEWSSYSTEM_DISPATCHER_H
