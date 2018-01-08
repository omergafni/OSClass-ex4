//
// Created by root on 1/1/18.
//

#include <iostream>
#include <unistd.h>
#include "ScreenManager.h"

ScreenManager::ScreenManager(SortedNewsQueue *queue) : queue(queue) {
    this->editorsDoneCounter = 0;
}

void ScreenManager::run() {

    string msg;
    while(this->editorsDoneCounter != 3){
        msg = readFromQueue();
        if(msg == "DONE"){
            this->editorsDoneCounter++;
        }
        else {
            printToScreen(msg);
        }
    }
    printToScreen("***** DONE *****");
}

string ScreenManager::readFromQueue() {
    return this->queue->pop();
}

void ScreenManager::printToScreen(string news) {
    cout << "[Screen] " << news << endl;
}
