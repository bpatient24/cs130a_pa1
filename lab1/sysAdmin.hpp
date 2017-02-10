//
//  sysAdmin.hpp
//  lab1
//
//  Created by Ben Patient on 2/9/17.
//  Copyright © 2017 Ben Patient. All rights reserved.
//

#ifndef sysAdmin_hpp
#define sysAdmin_hpp

#include <stdio.h>


class Event
{
public:
    Event(bool fix, int time, int target);
private:
    bool isFix; //fix or attack
    int time;
    int target;
};

class EventQueue: public Event
{
public:
    bool isEmpty();
private:
    int *data;
    int heapSize;
    int arraySize;
    void insertFixEvent(Event x);
    int getLeftChildIndex(int node);
    int getRightChildIndex(int node);
    int getParentIndex(int node);
    void percolateUp();
    void percolateDown();
    
};

class SysAdmin: public EventQueue
{
public:
    void alert();
private:
    void fix(int time, int target);  //Schedule a computer to be fixed. It can be compromised again.
    
};
#endif /* sysAdmin_hpp */
