//
// Created by root on 1/1/18.
//

#include <iostream>
#include "Producer.h"

Producer::Producer(int id,
                   vector<string> *news,
                   ProducerQueue *producerQueue) : id(id),
                                                   news(news),
                                                   producerQueue(producerQueue) {
    this->weatherCounter = 0;
    this->newsCounter = 0;
    this->sportCounter = 0;
}

void Producer::pushNew(string news) {
        producerQueue->push(news);
}

void Producer::run() {
    while(!(this->news->empty())){
        cout << "[Producer " << this->id << "] " << "pushing message \"" << this->news->back() << "\""<< endl;
        pushNew(this->news->back());
        this->news->pop_back();
    }
    pushNew("DONE");

}
