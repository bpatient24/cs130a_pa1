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
    
private:
    
    
};



class EventQueue
{
public:
    
private:
    int *data;
};

class SysAdmin: public EventQueue
{
public:
    
private:
    void fix(int time, int target);  //Schedule a computer to be fixed. It can be compromised again.
    void attack(int time, int source, int target);  //Schedule an attack event for time from source to target.
};
#endif /* sysAdmin_hpp */
