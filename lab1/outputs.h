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
        cout << "ATTACK(" << time << ",Attacker," << victim << ")" << endl;

    }
    else
    {
        cout << "ATTACK(" << time << "," << attacker << "," << victim << ")" << endl;
    }
}

void fixMessage(int time, int target)
{
        cout << "FIX(" << time << "," << target << ")" << endl;
}

void notifyMessage(int time, int attacker, int victim)
{
    if(attacker == - 1)
    {
        cout << "NOTIFY(" << time << ",Attacker," << victim << ")" << endl;
    }
    else
    {
        cout << "NOTIFY(" << time << "," << attacker << "," << victim << ")" << endl;
    }
}

void endMessage(int code, int time) // 1 = network wins; 2 = attacker wins; 3 = draw
{
    if(code == 1)
    {
        cout << "sysAdmin won in " << time << "milliseconds" << endl;
    }
    else if(code == 2)
    {
        cout << "attacker won in" << time << "milliseconds" << endl;
    }
    else
    {
        cout << "DRAW" << endl;
    }
}
#endif /* outputs_h */
