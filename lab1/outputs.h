//
//  outputs.h
//  lab1
//
//  Created by Ben Patient on 2/10/17.
//  Copyright © 2017 Ben Patient. All rights reserved.
//

#ifndef outputs_h
#define outputs_h

#include <string>
#include <iostream>


void attackMessage(unsigned long long int time, int attacker, int victim)
{
    if(attacker == - 1)
    {
        std::cout << "ATTACK(" << time << ",Attacker," << victim << ")" << std::endl;

    }
    else
    {
        std::cout << "ATTACK(" << time << "," << attacker << "," << victim << ")" << std::endl;
    }
}

void fixMessage(unsigned long long int time, int target)
{
        std::cout << "FIX(" << time << "," << target << ")" << std::endl;
}

void notifyMessage(unsigned long long int time, int attacker, int victim)
{
    if(attacker == - 1)
    {
        std::cout << "NOTIFY(" << time << ",Attacker," << victim << ")" << std::endl;
    }
    else
    {
        std::cout << "NOTIFY(" << time << "," << attacker << "," << victim << ")" << std::endl;
    }
}

void endMessage(int code) // 1 = network wins; 2 = attacker wins; 3 = draw
{
    if(code == 1)
    {
        std::cout << "sysadmin won!" << std::endl;
    }
    else if(code == 2)
    {
        std::cout << "attacker won!" << endl;
    }
    else
    {
        std::cout << "DRAW - time ran out" << endl;
    }
}
#endif /* outputs_h */
