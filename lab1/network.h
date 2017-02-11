//
//  network.h
//  lab1
//
//  Created by Ben Patient on 2/11/17.
//  Copyright © 2017 Ben Patient. All rights reserved.
//

#ifndef network_h
#define network_h

#include <string>
#include <stdlib.h>
#include <iostream>
#include "eventQueue.h"

class Attacker
{
public:
    int successRate;
    Attacker()
    {
        Attacker(50);
    }
    Attacker(int rate)
    {
        successRate = rate;
    }
    
    bool succesfulAttack()
    {
        return (rand() % 100 + 1) >= (100 - successRate);
    }
    
    void scheduleAttack(class EventQueue x, unsigned long long int time, int source, int target) // generates event to notify sysAdmin
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
    
    void attack(class Network network, int source, int target)
    {
        network.network[target].compromise();
    }
};





//COMPUTER DECLARATIONS *************************************************************************************
// computer default constructor
class Computer
{
public:
    int target;
    bool compromised;
    int location;
    Computer()
    {
        compromised = false;
        location = 0;
        target = 1;
    }
    
    //constructor
    Computer(int index)
    {
        compromised = false;
        location = index;
        target = 1;
    }
    
    void compromise()  //sets compromised to true.
    {
        compromised = true;
    }
    void fix()         //sets compromise to false.
    {
        compromised = false;
    };
    
    //SYSADMIN DECLARATIONS *************************************************************************************
class SysAdmin
    
    SysAdmin()
    {
        //infectedComputers.push_back(1);
        infectedComputers.reserve(100);
        cout << "SysAdmin Initialized" << endl;
    }
    
    void fix(class Network network, int fixTarget)
    {
        //add fix event and remove from infected list
        network.fixComputer(fixTarget);
        removeInfected(fixTarget);
    }
    
    void SysAdmin::scheduleFix(class EventQueue x, unsigned long long int time, int target)
    {
        Event fix;
        fix = Event(true, time, -2, target);
        x.addEvent(fix);
    }
    
    void SysAdmin::processNotify(Network network, int attacker, int victim)
    {
        //add infected to vector
        if(attacker > -1) //attacker is not attacker agent
        {
            //add attacker
            addInfected(attacker);
        }
        //add victim
        addInfected(victim);
    }
    
    void SysAdmin::percentInfected(Network net)
    {
        net.percentCompromised = (infectedComputers.size() / net.networkSize);
    }
    
    void SysAdmin::addInfected(int index)
    {
        cout << "VECTOR" << infectedComputers.size() << endl;
        //infectedComputers.get_allocator().allocate(2);
        infectedComputers.push_back(index);
    }
    
    void SysAdmin::removeInfected(int index)
    {
        infectedComputers.erase(remove(infectedComputers.begin(), infectedComputers.end(), index), infectedComputers.end());
    }
};



//IDS DECLARATIONS *************************************************************************************
//default constructor
IDS::IDS()
{
    detectRate = 50;
}
// IDS constructor
IDS::IDS(int rate)
{
    detectRate = rate;
    cout << "IDS Initialized" << endl;
};

bool IDS::detectedAttack(Network network)
{
    return (rand() % 100 + 1) >= (100 - network.detectRate);
}

void IDS::notify(Network network, SysAdmin sys, int attacker, int victim)
{
    if(attacker == -1)
    {
        if(detectedAttack(network))
        {
            sys.processNotify(network, attacker, victim);
        }
    }
    else
    {
        if(!((network.dividerIndex > attacker && network.dividerIndex > victim) || (network.dividerIndex < attacker && network.dividerIndex < victim))) // check to see if they crossed domains
        {
            if(detectedAttack(network))
            {
                sys.processNotify(network, attacker, victim);
            }
        }
    }
}

//NETWORK DECLARATIONS *************************************************************************************
//network defualt constructor
Network::Network()
{
    Network(0);
    cout << "Network default constructor" << endl;
}
//network constructor
Network::Network(int size)
{
    for(int i = 0; i < size; i++)
    {
        network.push_back(Computer(i));
    }
    if(size % 2 == 1)
    {
        dividerIndex = size / 2 + 1;
    }
    else
    {
        dividerIndex = size / 2;
    }
    networkSize = size;
    percentCompromised = 0;
    cout << "Network Properly Initialized" << endl;
}

bool Network::compromised()
{
    return percentCompromised > 50;
}
void Network::fixComputer(int index)
{
    network[index].fix();
}

//target
void Network::generateTarget(Computer x)
{
    x.target = rand() % networkSize + 1;
}


#endif /* network_h */
