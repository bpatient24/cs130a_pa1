//
//  event.h
//  lab1
//
//  Created by Ben Patient on 2/11/17.
//  Copyright © 2017 Ben Patient. All rights reserved.
//

#ifndef event_h
#define event_h

class Event
{
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
    
    //private:
};

#endif /* event_h */
