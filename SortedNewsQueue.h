//
// Created by root on 1/1/18.
//

#ifndef NEWSSYSTEM_SORTEDNEWSQUEUE_H
#define NEWSSYSTEM_SORTEDNEWSQUEUE_H


#include "BlockingQueue.h"

class SortedNewsQueue : public BlockingQueue{

private:
    string queueName;

public:
    string pop() override;
    void push(string item) override;

    SortedNewsQueue(const string &queueName);
};


#endif //NEWSSYSTEM_SORTEDNEWSQUEUE_H
