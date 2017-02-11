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

bool IDS::detectedAttack(int rate)
{
    return (rand() % 100 + 1) >= (100 - detectRate);
}

void IDS::notify(int attacker, int victim)
{
    
}

//NETWORK DECLARATIONS *************************************************************************************
//network defualt constructor
Network::Network()
{
    network[0] = Computer(0);
    cout << "Network default constructor" << endl;
}
//network constructor
Network::Network(int size)
{
    for(int i = 0; i < size; i++)
    {
        network.push_back(Computer(i));
    }
    cout << "Network Properly Initialized" << endl;
}

//target
void Network::generateTarget(Computer x)
{
    x.target = rand() % networkSize + 3;
    
}