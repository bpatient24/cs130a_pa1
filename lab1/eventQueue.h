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
    //default constructor
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
    int source; // -1 = attacker ; -2  = sysadmin
    int target;
    int eventIndex;
};


class EventQueue: public Event {
private:
    Event *event;
    int heapSize;
    int arraySize;
    
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
        event = new Event[size];
        heapSize = 0;
        arraySize = size;
    }
    
    int getMinimum()
    {
        if (isEmpty())
            throw string("QUEUE IS EMPTY");
        else
            return event[0].time;
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
        delete[] event;
    }
    
    //move up in the heap until sorted
    void percolateUp(int nodeIndex)
    {
        int parentIndex;
        Event temp;
        if (nodeIndex != 0)
        {
            parentIndex = getParentIndex(nodeIndex);
            if (event[parentIndex].time> event[nodeIndex].time)
            {
                temp = event[parentIndex];
                event[parentIndex] = event[nodeIndex];
                event[nodeIndex] = temp;
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
            if (event[leftChildIndex].time <= event[rightChildIndex].time)
                minIndex = leftChildIndex;
            else
                minIndex = rightChildIndex;
        }
        if (event[nodeIndex].time > event[minIndex].time)
        {
            temp = event[minIndex];
            event[minIndex] = event[nodeIndex];
            event[nodeIndex] = temp;
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
            if(event[0].isFix)
            {
                //dipatch fix event TODO
            }
            else
            {
                // dispatch attack event TODO
            }
            //remove event from queue
            event[0] = event[heapSize - 1];
            heapSize--;
            if (heapSize > 0)
                percolateDown(0);
        }
    }
    // create event to insert in queue
    void addEvent(Event action)
    {
        if (isFull())
        {
            //growArray(arraySize * 2);
            event[arraySize + 1] = action;
            arraySize++;
            heapSize++;
        }
        else
        {
            heapSize++;
            event[heapSize - 1] = action;
            percolateUp(heapSize - 1);
        }
    }
    
    void growArray(int size)
    {
        
    }
    
    /*void shrinkArray(int size)
    {
        //half the array
    }*/
};

EventQueue *priorityQueue;

#endif /* eventQueue_h */
