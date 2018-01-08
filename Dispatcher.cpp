//
// Created by root on 1/1/18.
//

#include <iostream>
#include <string>
#include "Dispatcher.h"

Dispatcher::Dispatcher(vector<ProducerQueue *> *producersQueues, SortedNewsQueue *sportQueue,
                       SortedNewsQueue *weatherQueue, SortedNewsQueue *newsQueue) : producersQueues(producersQueues),
                                                                                    sportQueue(sportQueue),
                                                                                    weatherQueue(weatherQueue),
                                                                                    newsQueue(newsQueue) {
    this->producerDoneCounter = 0;
}

void Dispatcher::run() {

    this->readFromProducersQueues();

    this->newsQueue->push("DONE");
    this->weatherQueue->push("DONE");
    this->sportQueue->push("DONE");

}

void Dispatcher::pushToSortedNewsQueue(string news) {

    if (news.find("news") != std::string::npos) {
        this->newsQueue->push(news);
        cout << "[Dispatcher] " << "pushed \"" << news << "\"" << " to news queue"<< endl;
    }
    if (news.find("weather") != std::string::npos) {
        this->weatherQueue->push(news);
        cout << "[Dispatcher] " << "pushed \"" << news << "\"" << " to weather queue"<< endl;
    }
    if (news.find("sport") != std::string::npos) {
        this->sportQueue->push(news);
        cout << "[Dispatcher] " << "pushed \"" << news << "\"" << " to sport queue"<< endl;
    }

}

void Dispatcher::readFromProducersQueues() {
    int i = 0;
    unsigned long queueSize = this->producersQueues->size();
    ProducerQueue *currentQueue;
    string msgFromQueue;

    while (this->producerDoneCounter != producersQueues->size()) {
        currentQueue = this->producersQueues->at(i % queueSize);
        msgFromQueue = currentQueue->pop();

        if (msgFromQueue == "DONE") {
            cout << "[Dispatcher] " << "received \"DONE\"" << endl;
            this->producerDoneCounter++;
        } else {
            pushToSortedNewsQueue(msgFromQueue);
        }

        i++;
    }

}
