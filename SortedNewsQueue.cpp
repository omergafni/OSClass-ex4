//
// Created by root on 1/1/18.
//

#include <iostream>
#include "SortedNewsQueue.h"

SortedNewsQueue::SortedNewsQueue(const string &queueName, int maxQueueSize) : queueName(queueName), maxQueueSize(maxQueueSize) {}

string SortedNewsQueue::pop() {

    std::unique_lock<std::mutex> mlock(_mutex);

    if (queue.empty()) {
        cond.wait(mlock);
    }

    string item = queue.front();
    queue.pop();
    mlock.unlock();
    cond.notify_one();

    return item;
}

void SortedNewsQueue::push(string item) {

    std::unique_lock<std::mutex> mlock(_mutex);

    if (this->queue.size() == this->maxQueueSize){
        cond.wait(mlock);
    }

    this->queue.push(item);
    // cout << "[" << this->queueName << " SortedNewsQueue] " << "received \"" << item << "\"" << endl;
    mlock.unlock();
    cond.notify_one();
}

