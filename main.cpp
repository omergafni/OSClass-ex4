#include <iostream>
#include <fstream>
#include "ProducerQueue.h"
#include "Producer.h"
#include "Dispatcher.h"
#include "CoEditor.h"
#include "ScreenManager.h"

using namespace std;
int main() {

    vector<ProducerQueue*>* producersQueuesVector = new vector<ProducerQueue*>();
    vector<Producer*>* producersVector = new vector<Producer*>();

    /*
     * Parse configuration file
     */

    // Create ProducerQueue queues
    ifstream inFile("configure.txt");
    string type;
    string newsCounter;
    string queueSize;
    string coEditorQueueSize;
    int producerCounter = 0;
    while(1){
        getline(inFile, type);
        if (type == "C") {
            break;
        }
        producerCounter++;
        getline(inFile, newsCounter);
        getline(inFile, queueSize);
        ProducerQueue* pq = new ProducerQueue(stoi(queueSize));
        producersQueuesVector->push_back(pq);
        producersVector->push_back(new Producer(producerCounter, stoi(newsCounter), pq));
    }
    getline(inFile, coEditorQueueSize);
    inFile.close();

    /*
     * Initialization
     */

    // Create CoEditor queues
    SortedNewsQueue* sortedNewsQueue = new SortedNewsQueue("News", stoi(coEditorQueueSize));
    SortedNewsQueue* sortedSportQueue = new SortedNewsQueue("Sport", stoi(coEditorQueueSize));
    SortedNewsQueue* sortedWeatherQueue = new SortedNewsQueue("Weather", stoi(coEditorQueueSize));

    // Create screen manager
    SortedNewsQueue* screenManagerQueue = new SortedNewsQueue("Screen Manager", stoi(coEditorQueueSize));
    ScreenManager* screenManager = new ScreenManager(screenManagerQueue);

    // Create CoEditor(s) (3 thread)
    CoEditor* editor1 = new CoEditor(sortedNewsQueue, screenManagerQueue, "News");
    CoEditor* editor2 = new CoEditor(sortedWeatherQueue, screenManagerQueue, "Weather");
    CoEditor* editor3 = new CoEditor(sortedSportQueue, screenManagerQueue, "Sports");

    // Create Dispatcher (thread)
    Dispatcher* dispatcher = new Dispatcher(producersQueuesVector, sortedSportQueue, sortedWeatherQueue, sortedNewsQueue);


    /*
     * Start threads
     */

    // Producers:
    for(int i = 0; i < producersVector->size(); i++){
        producersVector->at(i)->start();
    }
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