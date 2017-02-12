//
//  attacker.h
//  lab1
//
//  Created by Ben Patient on 2/11/17.
//  Copyright © 2017 Ben Patient. All rights reserved.
//

#ifndef attacker_h
#define attacker_h

class Attacker
{
public:
    Attacker()
    {
        successRate = 50;
    }
    Attacker(int rate)
    {
        successRate = rate;
    }
    void attack(Network network, int source, int target) // generates event to notify sysAdmin
    {
        network.network[target].compromise();
    }

    void scheduleAttack(EventQueue <Event> x, unsigned long long int time, int source, int target)
    {
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
    int successRate;
    bool succesfulAttack()
    {
        return (rand() % 100 + 1) >= (100 - successRate);
    }
private:
};

#endif /* attacker_h */
