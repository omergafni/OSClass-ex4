//
// Created by root on 1/1/18.
//

#ifndef NEWSSYSTEM_PRODUCER_H
#define NEWSSYSTEM_PRODUCER_H

#include <vector>
#include <string>
#include "ProducerQueue.h"
#include "MThread.h"

using namespace std;

class Producer : public MThread{

    int id;
    int weatherCounter, sportCounter, newsCounter;
    vector<string>* news;
    ProducerQueue* producerQueue;

    string randomType();
    void pushNew(string news);

public:

    Producer(int id, int newsNumber, ProducerQueue *producerQueue);
    void run() override;
    vector<string>* generateNews(int number);
};


#endif //NEWSSYSTEM_PRODUCER_H
