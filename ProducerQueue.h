//
// Created by root on 1/1/18.
//

#ifndef NEWSSYSTEM_PRODUCERQUEUE_H
#define NEWSSYSTEM_PRODUCERQUEUE_H

#include <string>
#include <condition_variable>
#include <queue>
#include "BlockingQueue.h"

using namespace std;

class ProducerQueue : public BlockingQueue {

    int maxQueueSize;

public:

    ProducerQueue(int maxQueueSize);

    // pop an element and return a copy. Block if queue empty.
    string pop() override;
    void push(string item) override;

};


#endif //NEWSSYSTEM_PRODUCERQUEUE_H
