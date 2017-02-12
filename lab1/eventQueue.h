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
#include <utility>
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
    //int eventIndex;
    //default constructor
    Event()
    {
        //Event(true, 1, -3, -3);
        isFix = NULL;
        time = NULL;
        source = NULL;
        target = NULL;
        //eventIndex = NULL;
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

template <typename Event>
class EventQueue
{
public:
    int heapSize;
    int arraySize;
    Event *queue = new Event[100];
    
    
    //constructor
    EventQueue()
    {
        //EventQueue(10);
        queue = new Event[10];
        heapSize = 0;
        arraySize = 10;
    }
    
    EventQueue(int size)
    {
        queue = new Event[size];
        heapSize = 0;
        arraySize = size;
    }
    
    // create event to insert in queue
    void addEvent(const Event &e)
    {
        if(heapSize == arraySize -1)
        {
            doubleArray(arraySize);
        }
        
        
        int oldSize = ++arraySize;
        Event copy = e;
        
        //queue[oldSize] = copy;
       // percolateUp(oldSize);
        
        queue[0] = move(copy);
        for( ; copy < queue[oldSize/2]; oldSize /= 2)
        {
            queue[oldSize] = move(queue[oldSize/2]);
        }
        queue[oldSize] = move(queue[0]);
    }
    
    bool isEmpty()
    {
        return (heapSize == 0);
    }
    
    bool isFull()
    {
        return (heapSize == arraySize);
    }
    
    void deleteMin(Event &nextEvent)
    {
        if(isEmpty())
        {
            cout << "NO QUEUE EVENTS" << endl;
        }
        
        nextEvent = move(queue[1]);
        queue[1] = move (queue[arraySize--]);
        percolateDown(1);
    }
    
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
    
    //move up in the heap until sorted
    void percolateUp(int nodeIndex)
    {
        //cout << "TEST" << endl;
        int parentIndex;
        Event temp;
        if (nodeIndex != 0)
        {
            parentIndex = getParentIndex(nodeIndex);
            if (queue[parentIndex]> queue[nodeIndex])
            {
                temp = queue[parentIndex];
                queue[parentIndex] = queue[nodeIndex];
                queue[nodeIndex] = temp;
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
        Event temp = move(queue[nodeIndex]);
        
        cout << "PERCOLATED DOWN 1" << endl;
        
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
            if (queue[leftChildIndex] <= queue[rightChildIndex])
                minIndex = leftChildIndex;
            else
                minIndex = rightChildIndex;
        }
        if (queue[nodeIndex] > queue[minIndex])
        {
            temp = queue[minIndex];
            queue[minIndex] = queue[nodeIndex];
            queue[nodeIndex] = temp;
            percolateDown(minIndex);
        }
    }
    
    void doubleArray(int size)
    {
        //GROW ARRAY
        Event *newArray = new Event[size*2];
        for(int i = 0; i < size; i++)
        {
            newArray[i] = queue[i];
        }
        arraySize = size * 2;
        delete [] queue;
        queue = newArray;
    }
    
    bool operator > (const Event &e) const
    {
        return this->time > e.time;
    }
    
    bool operator < (const Event &e) const
    {
        return this->time < e.time;
    }
    
    bool operator >= (const Event &e) const
    {
        return this->time >= e.time;
    }
    
    bool operator <= (const Event &e) const
    {
        return this->time <= e.time;
    }
    
    bool operator == (const Event &e) const
    {
        return this->time == e.time;
    }
};

#endif /* eventQueue_h */
