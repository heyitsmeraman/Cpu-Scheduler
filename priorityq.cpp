#include "priorityQ.h"

bool comparePriority(const process &p1, const process &p2)
{
    if (p1.pr == p2.pr)
    {
        // If priorities are equal, compare burst times
        return p1.bt < p2.bt;
    }
    else
    {
        // If priorities are different, compare them directly
        return p1.pr < p2.pr;
    }
}

// Insert a process into the priority queue
void PriorityQueue::insert(const process &p)
{
    processes.push_back(p);
    // Bubble up the inserted process to maintain the heap property
    int idx = processes.size() - 1;
    while (idx > 0 && comparePriority(processes[idx], processes[(idx - 1) / 2]))
    {
        swap(processes[idx], processes[(idx - 1) / 2]);
        idx = (idx - 1) / 2;
    }
}

// Remove and return the highest priority process from the priority queue
process PriorityQueue::extractMin()
{
    /*if (processes.empty())
    {
        // Handle empty queue
        cout << "Priority queue is empty!" << endl;
        return process{-1, -1, -1, -1}; // Return a dummy process
    }*/
    //else
    //{
    process minprocess = processes[0];
    processes[0] = processes[processes.size() - 1]; // Move the last process to the root
    processes.pop_back();

    // Bubble down the swapped process to maintain the heap property
    int idx = 0;
    while (true)
    {
        int leftChild = 2 * idx + 1;
        int rightChild = 2 * idx + 2;
        int smallest = idx;

        if (leftChild < processes.size() && comparePriority(processes[leftChild], processes[smallest]))
        {
            smallest = leftChild;
        }
        if (rightChild < processes.size() && comparePriority(processes[rightChild], processes[smallest]))
        {
            smallest = rightChild;
        }
        if (smallest != idx)
        {
            swap(processes[idx], processes[smallest]);
            idx = smallest;
        }
        else
        {
            break;
        }
    }
    return minprocess;
    //}
}

bool PriorityQueue::isEmpty()
{
    return processes.empty();
}
