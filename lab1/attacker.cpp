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

void Attacker::scheduleAttack(class EventQueue x, unsigned long long int time, int source, int target) // generates event to notify sysAdmin
{                                                                                  // source == -1 for attacker
    //add attack to event queue
    if(succesfulAttack())
    {
        if(source == -1)
        {
            Event attack;
            attack = Event(false, time, -1, target);
            x.addEvent(attack);
        }
        else if(source > -1)
        {
            Event attack;
            attack = Event(false, time, source, target);
            x.addEvent(attack);
        }
    }
}

void Attacker::attack(class Network network, int source, int target)
{
    network.network[target].compromise();
}