//
//  attacker.cpp
//  lab1
//
//  Created by Ben Patient on 2/9/17.
//  Copyright © 2017 Ben Patient. All rights reserved.
//

#include "eventQueue.h"
#include "attacker.hpp"
#include <stdlib.h>
#include <iostream>

Attacker::Attacker()
{
    Attacker(50);
}
Attacker::Attacker(int rate)
{
    successRate = rate;
}

bool Attacker::succesfulAttack()
{
    return (rand() % 100 + 1) >= (100 - successRate);
}

void Attacker::attack(int time, int source, int target) // generates event to notify sysAdmin
{                                                       // source == -1 for attacker
    
    if(succesfulAttack())
    {
        //add attack to event queue
        Event attack;
        attack = Event(true, time, -2, target);
        priorityQueue->addEvent(attack);
    }
}