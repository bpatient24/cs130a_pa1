//
//  network.cpp
//  lab1
//
//  Created by Ben Patient on 2/9/17.
//  Copyright © 2017 Ben Patient. All rights reserved.
//

#include "network.hpp"
#include "sysAdmin.hpp"
#include <stdlib.h>

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

//IDS DECLARATIONS *************************************************************************************
// IDS constructor
IDS::IDS(int rate)
{
    detectRate = rate;
};

void IDS::computerAttacked(int attacker, int victim)
{
    int attackerIndex = attacker;
    int victimIndex = victim;
    
}

//NETWORK DECLARATIONS *************************************************************************************
//network defualt constructor
Network::Network()
{
    network[0] = Computer(0);
}
//network constructor
Network::Network(int size)
{
    for(int i = 0; i < size; i++)
    {
        network.push_back(Computer(i));
    }
}

//target
void Network::generateTarget(Computer x)
{
    x.target = rand() % networkSize + 3;
    
}