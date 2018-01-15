//
// Created by root on 1/1/18.
//

#include <iostream>
#include "Producer.h"
#include <cstdlib>
#include <algorithm>

Producer::Producer(int id,
                   int newsNumber,
                   ProducerQueue *producerQueue) : id(id), producerQueue(producerQueue) {
    this->weatherCounter = 0;
    this->newsCounter = 0;
    this->sportCounter = 0;
    this->news = generateNews(newsNumber);
}

void Producer::pushNew(string news) {
        producerQueue->push(news);
}

void Producer::run() {
    while(!(this->news->empty())){
        // cout << "[Producer " << this->id << "] " << "pushing message \"" << this->news->back() << "\""<< endl;
        pushNew(this->news->back());
        this->news->pop_back();
    }
    pushNew("DONE");

}

vector<string> *Producer::generateNews(int number) {

    vector<string>* generatedNews = new vector<string>();
    for(int i = 0; i < number; i++){
        string news = "producer " + to_string(this->id) + " " + randomType();
        generatedNews->push_back(news);
    }

    reverse(generatedNews->begin(), generatedNews->end());
    return generatedNews;
}

string Producer::randomType() {

    string news = "news";
    string weather = "weather";
    string sport = "sport";
    int r = rand() % 3;

    if (r==0){
        this->newsCounter++;
        return news + " " + to_string(this->newsCounter);
    }
    else if (r==1){
        this->weatherCounter++;
        return weather + " " + to_string(this->weatherCounter);
    }
    else{
        this->sportCounter++;
        return sport + " " + to_string(this->sportCounter);
    }

}
