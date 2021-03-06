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
    //friend class EventQueue;
public:
    
    unsigned long long int time;
    int target;
    bool isFix; //fix or attack
    int source; // -1 = attacker ; -2  = sysadmin
    int eventIndex;
    //default constructor
    Event()
    {
        //Event(true, 1, -3, -3);
        isFix = NULL;
        time = NULL;
        source = NULL;
        target = NULL;
        eventIndex = NULL;
    }
    // constructor
    Event(bool fix, unsigned long long int timeForEvent, int eventSource, int targetForEvent)
    {
        isFix = fix;
        time = timeForEvent;
        source = eventSource;
        target = targetForEvent;
    }
    
    //private:
};


class EventQueue: public Event {
//private:
public:
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
    
    EventQueue()
    {
        //EventQueue(10);
        event = new Event[10];
        heapSize = 0;
        arraySize = 10;
    }
    
    EventQueue(int size)
    {
        event = new Event[size];
        heapSize = 0;
        arraySize = size;
    }
    
    unsigned long long int getMinimum()
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
    
    /*~EventQueue()
     {
     delete[] event;
     }*/
    
    //move up in the heap until sorted
    void percolateUp(int nodeIndex)
    {
        //cout << "TEST" << endl;
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
            int oldSize = arraySize;
            doubleArray(arraySize);
            event[oldSize + 1] = action;
            heapSize++;
        }
        else
        {
            cout << "hi" << endl;
            heapSize++;
            cout << heapSize << ", " << arraySize << endl;
            event[heapSize - 1] = action;
            cout << "bye" << endl;
            percolateUp(heapSize - 1);
        }
    }
    
    void doubleArray(int size)
    {
        //GROW ARRAY
        Event *newArray = new Event[size*2];
        for(int i = 0; i < size; i++)
        {
            newArray[i] = event[i];
        }
        arraySize = size * 2;
        delete [] event;
        event = newArray;
    }
};

#endif /* eventQueue_h */
