//
// Created by root on 1/1/18.
//

#include "ProducerQueue.h"
#include <thread>
#include <mutex>
#include <iostream>

ProducerQueue::ProducerQueue(int maxQueueSize) : maxQueueSize(maxQueueSize) {}

string ProducerQueue::pop() {

    std::unique_lock<std::mutex> mlock(_mutex);

    if(queue.empty()){
        mlock.unlock();
        return "EMPTY";
    }

    string item = queue.front();
    queue.pop();
    mlock.unlock();
    cond.notify_one();

    return item;
}

void ProducerQueue::push(string item) {

    std::unique_lock<std::mutex> mlock(_mutex);

    if (this->queue.size() == this->maxQueueSize){
        cond.wait(mlock);
    }

    this->queue.push(item);
    cout << "[ProducerQueue] " << "received \"" << item<< "\"" << endl;
    mlock.unlock();
}

