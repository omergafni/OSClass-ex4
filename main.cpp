#include <iostream>
#include "ProducerQueue.h"
#include "Producer.h"
#include "Dispatcher.h"
#include "CoEditor.h"
#include "ScreenManager.h"

using namespace std;
int main() {

    SortedNewsQueue* sortedNewsQueue = new SortedNewsQueue("News");
    SortedNewsQueue* sortedSportQueue = new SortedNewsQueue("Sport");
    SortedNewsQueue* sortedWeatherQueue = new SortedNewsQueue("Weather");
    SortedNewsQueue* screenManagerQueue = new SortedNewsQueue("Screen Manager");

    vector<string>* producer1_news = new vector<string>();
    producer1_news->push_back("producer 1 sport 0"); producer1_news->push_back("producer 1 news 0"); producer1_news->push_back("producer 1 weather 1");

    vector<string>* producer2_news = new vector<string>();
    producer2_news->push_back("producer 2 sport 0"); producer2_news->push_back("producer 2 news 0"); producer2_news->push_back("producer 2 weather 1");

    vector<string>* producer3_news = new vector<string>();
    producer3_news->push_back("producer 3 sport 0"); producer3_news->push_back("producer 3 news 0"); producer3_news->push_back("producer 3 weather 1");

    vector<string>* producer4_news = new vector<string>();
    producer4_news->push_back("producer 4 sport 0"); producer4_news->push_back("producer 4 news 0"); producer4_news->push_back("producer 4 weather 1");


    vector<ProducerQueue*>* producersQueuesVector = new vector<ProducerQueue*>();

    // Create ProducerQueue queues
    ProducerQueue* pq1 = new ProducerQueue(2);
    ProducerQueue* pq2 = new ProducerQueue(1);
    ProducerQueue* pq3 = new ProducerQueue(3);
    ProducerQueue* pq4 = new ProducerQueue(10);


    // Create Producer(s) (N threads)
    Producer* producer1 = new Producer(1, producer1_news, pq1);
    producersQueuesVector->push_back(pq1);

    Producer* producer2 = new Producer(2, producer2_news, pq2);
    producersQueuesVector->push_back(pq2);

    Producer* producer3 = new Producer(3, producer3_news, pq3);
    producersQueuesVector->push_back(pq3);

    Producer* producer4 = new Producer(4, producer4_news, pq4);
    producersQueuesVector->push_back(pq4);


    // Create Dispatcher (thread)
    Dispatcher* dispatcher = new Dispatcher(producersQueuesVector, sortedSportQueue, sortedWeatherQueue, sortedNewsQueue);

    // Create CoEditor(s) (3 thread)
    CoEditor* editor1 = new CoEditor(sortedNewsQueue, screenManagerQueue, "News");
    CoEditor* editor2 = new CoEditor(sortedWeatherQueue, screenManagerQueue, "Weather");
    CoEditor* editor3 = new CoEditor(sortedSportQueue, screenManagerQueue, "Sports");

    // Create screen manager
    ScreenManager* screenManager = new ScreenManager(screenManagerQueue);

    // Run threads
    producer1->start();
    producer2->start();
    producer3->start();
    producer4->start();
    dispatcher->start();
    editor1->start();
    editor2->start();
    editor3->start();
    screenManager->start();
    
    screenManager->waitForThread();
    return 0;
}