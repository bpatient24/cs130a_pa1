//
//  ids.h
//  lab1
//
//  Created by Ben Patient on 2/11/17.
//  Copyright © 2017 Ben Patient. All rights reserved.
//

#ifndef ids_h
#define ids_h

#include "network.h"


class IDS //: public SysAdmin
{
public:
    IDS()
    {
        detectRate = 50;
    }
    IDS(int rate)
    {
        detectRate = rate;
        cout << "IDS Initialized" << endl;
    }
    void notify(class Network network, int time, int attacker, int victim) // generates event to notify sysAdmin
    {
        if(attacker == -1)
        {
            if(detectedAttack())
            {
                notifyMessage(time, attacker, victim);
            }
        }
        else
        {
            if(!((network.dividerIndex > attacker && network.dividerIndex > victim) || (network.dividerIndex < attacker && network.dividerIndex < victim))) // check to see if they crossed domains
            {
                if(detectedAttack())
                {
                    notifyMessage(time, attacker, victim);
                }
            }
        }
    }
    int detectRate;
    bool detectedAttack()
    {
        return (rand() % 100 + 1) >= (100 - detectRate);
    }
    //private:
};

#endif /* ids_h */
