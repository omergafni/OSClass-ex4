//
// Created by root on 1/1/18.
//

#ifndef NEWSSYSTEM_COEDITOR_H
#define NEWSSYSTEM_COEDITOR_H


#include "SortedNewsQueue.h"
#include "ProducerQueue.h"
#include "MThread.h"

class CoEditor : public MThread {

    SortedNewsQueue* queue;
    SortedNewsQueue* screenManagerQueue;
    string editorName;

public:

    CoEditor(SortedNewsQueue *queue, SortedNewsQueue *screenManagerQueue, const string &editorName);

    string readFromQueue();
    void pushToScreenManagerQueue(string news);

    void run() override;
};


#endif //NEWSSYSTEM_COEDITOR_H
