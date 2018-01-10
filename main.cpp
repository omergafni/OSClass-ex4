#include <iostream>
#include <fstream>
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

    vector<ProducerQueue*>* producersQueuesVector = new vector<ProducerQueue*>();
    vector<Producer*>* producerVector = new vector<Producer*>();
    // Create ProducerQueue queues
    ifstream inFile("configure.txt");
    string type;
    string newsCounter;
    string queueSize;
    int producerCounter = 0;
    while(1){
        getline(inFile, type);
        if (type == "C")
            break;
        producerCounter++;
        getline(inFile, newsCounter);
        getline(inFile, queueSize);
        ProducerQueue* pq = new ProducerQueue(stoi(queueSize));
        producersQueuesVector->push_back(pq);
        producerVector->push_back(new Producer(producerCounter, stoi(newsCounter), pq));
    }


    ProducerQueue* pq1 = new ProducerQueue(2);
    ProducerQueue* pq2 = new ProducerQueue(1);
    ProducerQueue* pq3 = new ProducerQueue(3);
    ProducerQueue* pq4 = new ProducerQueue(10);


    // Create Producer(s) (N threads)
    Producer* producer1 = new Producer(1, 5, pq1);
    producersQueuesVector->push_back(pq1);

    Producer* producer2 = new Producer(2, 7, pq2);
    producersQueuesVector->push_back(pq2);

    Producer* producer3 = new Producer(3, 6, pq3);
    producersQueuesVector->push_back(pq3);

    Producer* producer4 = new Producer(4, 8, pq4);
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

    cout << "Press any key to exit." << endl;
    getchar();
    return 0;
}