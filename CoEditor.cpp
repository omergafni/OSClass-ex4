//
// Created by root on 1/1/18.
//

#include <iostream>
#include <unistd.h>
#include "CoEditor.h"


CoEditor::CoEditor(SortedNewsQueue *queue, SortedNewsQueue *screenManagerQueue, const string &editorName) : queue(
        queue), screenManagerQueue(screenManagerQueue), editorName(editorName) {}

void CoEditor::run() {

    string msg;

    do{
        msg = readFromQueue();
        pushToScreenManagerQueue(msg);
        cout << "[" << this->editorName << " CoEditor] " << "received \"" << msg << "\"" << endl;

    }
    while(msg != "DONE");
    pushToScreenManagerQueue("DONE");
}

string CoEditor::readFromQueue() {
    return this->queue->pop();
}

void CoEditor::pushToScreenManagerQueue(string news) {
    sleep(0.1);
    this->screenManagerQueue->push(news);
}
