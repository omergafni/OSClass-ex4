//
// Created by root on 1/1/18.
//

#ifndef NEWSSYSTEM_BLOCKINGQUEUE_H
#define NEWSSYSTEM_BLOCKINGQUEUE_H

#include <string>
#include <condition_variable>
#include <queue>

using namespace std;

class BlockingQueue {

protected:
    std::queue<string> queue;
    std::mutex _mutex;
    std::condition_variable cond;

public:
    // pop an element and return a copy. Block if queue empty.
    virtual string pop() = 0;

    //  push an element to the back of the queue.
    virtual void push(string item) = 0;

};


#endif //NEWSSYSTEM_BLOCKINGQUEUE_H
