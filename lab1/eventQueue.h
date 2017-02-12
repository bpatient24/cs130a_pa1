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
//#include "network.hpp"
#include "event.h"

using namespace std;

template <typename Event>
class EventQueue
{
public:
    int heapSize;
    int arraySize;
    Event *queue;
    
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
        if(isFull())
        {
            //GROW ARRAY
            Event *newArray = new Event[heapSize*2];
            for(int i = 0; i < heapSize; i++)
            {
                newArray[i] = queue[i];
            }
            arraySize = heapSize * 2;
            delete [] queue;
            queue = newArray;
        }
        
        int hole = ++heapSize;
        Event copy = e;
       // percolateUp(oldSize);
        queue[0] = move(copy);
        for( ; copy < queue[hole/2]; hole /= 2)
        {
            queue[hole] = move(queue[hole/2]);
        }
        queue[hole] = move(queue[0]);
    }
    
    bool isEmpty()
    {
        return (heapSize == 0);
    }
    
    bool isFull()
    {
        return (heapSize == arraySize - 1);
    }
    
    void deleteMin(Event &nextEvent)
    {
        if(isEmpty())
        {
            cout << "NO QUEUE EVENTS" << endl;
        }
        
        nextEvent = move(queue[1]);
        queue[1] = move (queue[heapSize--]);
        percolateDown(1);
    }
    
    int getLeftChildIndex(int nodeIndex)
    {
        return 2 * nodeIndex;
    }
    
    int getRightChildIndex(int nodeIndex)
    {
        return 2 * nodeIndex + 1;
    }
    
    int getParentIndex(int nodeIndex)
    {
        return nodeIndex / 2;
    }
    
    void percolateDown(int hole)
    {
        int child;
        Event temp = move(queue[hole]);
        for( ; hole*2 <= heapSize; hole = child)
        {
            child = hole*2;
            if (child != heapSize && queue[child + 1] < queue[child])
            {
                child++;
            }
            if (queue[child] < temp)
            {
                queue[hole] = move(queue[child]);
            }
            else break;
        }
        queue[hole] = move(temp);
    }
    
    void percolateUp(int index)
    {
        Event copy = move(queue[index]);
        queue[0] = move(copy);
        for( ; copy < queue[index/2]; index /= 2)
        {
            queue[index] = move(queue[index/2]);
        }
        queue[index] = move(queue[0]);
    }
    
    
    //move up in the heap until sorted
    /*void percolateUp(int nodeIndex)
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
    }*/
    
    //void doubleArray(int size)
    
    
    /*Event &operator[] (int i)
    {
        if(i > arraySize)
        {
            cout << "OUT OF BOUNDS" << endl;
        }
        return queue[i];
    }*/
};

#endif /* eventQueue_h */
