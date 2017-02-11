//
//  network.cpp
//  lab1
//
//  Created by Ben Patient on 2/9/17.
//  Copyright © 2017 Ben Patient. All rights reserved.
//

#include "network.hpp"
#include <stdlib.h>
#include <iostream>
#include "eventQueue.h"

//COMPUTER DECLARATIONS *************************************************************************************
// computer default constructor
Computer::Computer()
{
    compromised = false;
    location = 0;
    target = 1;
}

//constructor
Computer::Computer(int index)
{
    compromised = false;
    location = index;
    target = 1;
}

void Computer::compromise()  //sets compromised to true.
{
    compromised = true;
    
}
void Computer::fix()         //sets compromise to false.
{
    compromised = false;
};

//SYSADMIN DECLARATIONS *************************************************************************************
SysAdmin::SysAdmin()
{
    cout << "SysAdmind Initialized" << endl;
}

void SysAdmin::fix(class Network network, int timeForFix, int fixTarget)
{
    //TODO add fix event and remove from infected list
    network.fixComputer(fixTarget);
    removeInfected(fixTarget);
}

void SysAdmin::scheduleFix(int time, int target) 
{
    Event fix;
    fix= Event(true, time, -2, target);
    priorityQueue->addEvent(fix);
}

void SysAdmin::processNotify(Network network, int attacker, int victim)
{
    //TODO add infected to vector
    if(attacker > -1) //attacker is not attacker agent
    {
        //add attacker
        addInfected(attacker);
    }
    //add victim
    addInfected(victim);
}

void SysAdmin::addInfected(int index)
{
    infectedComputers.push_back(index);
}

void SysAdmin::removeInfected(int index)
{
    infectedComputers.erase(remove(infectedComputers.begin(), infectedComputers.end(), index), infectedComputers.end());
}

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

void IDS::notify(Network network, int attacker, int victim)
{
    if(attacker == -1)
    {
        if(detectedAttack(network))
        {
            processNotify(network, attacker, victim);
        }
    }
    else
    {
        if(!((network.dividerIndex > attacker && network.dividerIndex > victim) || (network.dividerIndex < attacker && network.dividerIndex < victim))) // check to see if they crossed domains
        {
            if(detectedAttack(network))
            {
                processNotify(network, attacker, victim);
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

    {        dividerIndex = size / 2;
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
    x.target = rand() % networkSize + 3;
}










