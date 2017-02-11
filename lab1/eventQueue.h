//
//  eventQueue.h
//  lab1
//
//  Created by Ben Patient on 2/10/17.
//  Copyright © 2017 Ben Patient. All rights reserved.
//

#ifndef eventQueue_h
#define eventQueue_h

#include <string>
#include <stdlib.h>
#include <iostream>
#include "network.hpp"

using namespace std;

class Event
{
    friend class EventQueue;
public:
    //defualt constructor
    Event()
    {
        isFix = NULL;
        time = NULL;
        source = NULL;
        target = NULL;
        eventIndex = NULL;
    }
    // constructor
    Event(bool fix, int timeForEvent, int eventSource, int targetForEvent)
    {
        isFix = fix;
        time = timeForEvent;
        source = eventSource;
        target = targetForEvent;
    }

private:
    bool isFix; //fix or attack
    int time;
    int source;
    int target;
    int eventIndex;
};


class EventQueue: public Event {
private:
    Event *priorityQueue;
    int heapSize;
    int arraySize;
    int dividerIndex;
    
    int getLeftChildIndex(int nodeIndex)
    {
        return 2 * nodeIndex + 1;
    }
    
    int getRightChildIndex(int nodeIndex)
    {
        return 2 * nodeIndex + 2;
    }
    
    int getParentIndex(int nodeIndex)
    {
        return (nodeIndex - 1) / 2;
    }
    
public:
    EventQueue()
    {
        EventQueue(1);
    }
    
    EventQueue(int size)
    {
        priorityQueue = new Event[size];
        heapSize = 0;
        arraySize = size;
        dividerIndex = 0;
    }
    
    int getMinimum()
    {
        if (isEmpty())
            throw string("QUEUE IS EMPTY");
        else
            return priorityQueue[0].time;
    }
    
    bool isEmpty()
    {
        return (heapSize == 0);
    }
    
    bool isFull()
    {
        return (heapSize == arraySize);
    }
    
    ~EventQueue()
    {
        delete[] priorityQueue;
    }
    
    //move up in the heap until sorted
    void percolateUp(int nodeIndex)
    {
        int parentIndex;
        Event temp;
        if (nodeIndex != 0)
        {
            parentIndex = getParentIndex(nodeIndex);
            if (priorityQueue[parentIndex].time> priorityQueue[nodeIndex].time)
            {
                temp = priorityQueue[parentIndex];
                priorityQueue[parentIndex] = priorityQueue[nodeIndex];
                priorityQueue[nodeIndex] = temp;
                percolateUp(parentIndex);
            }
        }
    }
    //move down in heap until sorted
    void percolateDown(int nodeIndex)
    {
        int leftChildIndex;
        int rightChildIndex;
        int minIndex;
        Event temp;
        
        leftChildIndex = getLeftChildIndex(nodeIndex);
        rightChildIndex = getRightChildIndex(nodeIndex);
        
        if (rightChildIndex >= heapSize)
        {
            if (leftChildIndex >= heapSize)
                return;
            else
                minIndex = leftChildIndex;
        }
        else
        {
            if (priorityQueue[leftChildIndex].time <= priorityQueue[rightChildIndex].time)
                minIndex = leftChildIndex;
            else
                minIndex = rightChildIndex;
        }
        if (priorityQueue[nodeIndex].time > priorityQueue[minIndex].time)
        {
            temp = priorityQueue[minIndex];
            priorityQueue[minIndex] = priorityQueue[nodeIndex];
            priorityQueue[nodeIndex] = temp;
            percolateDown(minIndex);
        }
    }
    //dispatch event
    void removeMin()
    {
        if (isEmpty())
            throw string("QUEUE IS EMPTY");
        else
        {
            if(priorityQueue[0].isFix)
            {
                //dipatch fix event
            }
            else
            {
                // dispatch attack event
            }
            //remove event from queue
            priorityQueue[0] = priorityQueue[heapSize - 1];
            heapSize--;
            if (heapSize > 0)
                percolateDown(0);
        }
    }
    // create event to insert in queue
    void insert(Event event)
    {
        if (isFull())
        {
            //growArray(arraySize * 2);
            priorityQueue[arraySize + 1] = event;
            arraySize++;
            heapSize++;
        }
        else
        {
            heapSize++;
            priorityQueue[heapSize - 1] = event;
            percolateUp(heapSize - 1);
        }
    }
    
    /*void growArray(int size)
    {
        
    }*/
    
    /*void shrinkArray(int size)
    {
        //half the array
    }*/
};

#endif /* eventQueue_h */
