#ifndef PRIORITYQ_H
#define PRIORITYQ_H

#include "mainwindow.h"
#include <vector>
//#include <iostream>
//using namespace std;

bool comparePriority(const process &p1, const process &p2);

class PriorityQueue
{
private:
    vector<process> processes;

public:
    void insert(const process &p);
    process extractMin();
    bool isEmpty();
};

#endif // PRIORITYQ_H
