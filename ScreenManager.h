//
// Created by root on 1/1/18.
//

#ifndef NEWSSYSTEM_SCREENMANAGER_H
#define NEWSSYSTEM_SCREENMANAGER_H

#include <string>
#include "ProducerQueue.h"
#include "MThread.h"
#include "SortedNewsQueue.h"

using namespace std;

class ScreenManager : public MThread {

    SortedNewsQueue* queue;
    int editorsDoneCounter;
    string queueName;
public:
    ScreenManager(SortedNewsQueue* queue);

public:
    string readFromQueue();
    void printToScreen(string news);
    void run() override;
};


#endif //NEWSSYSTEM_SCREENMANAGER_H
