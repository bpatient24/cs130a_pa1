//
//  main.cpp
//  lab1
//
//  Created by Ben Patient on 2/9/17.
//  Copyright © 2017 Ben Patient. All rights reserved.
//

#include <iostream>
#include <string>
#include "eventQueue.h"
#include "network.hpp"
#include "attacker.hpp"
#include "outputs.h"


using namespace std;

// -1 = attacker ; -2  = sysadmin
int simulateAttack(int numComputers, int attackPercent, int detectPercent)
{
    int exitCode;
    unsigned long long int time = 0; //time in ms
    unsigned long long int maxTime = 8640000000;
    bool firstLoop = true;
    Network networkUnderAttack = Network(numComputers);
    SysAdmin sysadmin = SysAdmin();
    IDS ids = IDS(detectPercent);
    Attacker attacker = Attacker(attackPercent);
    while((networkUnderAttack.compromised() != true) && (time < maxTime) && ((firstLoop) || !(networkUnderAttack.percentCompromised == 0)) )
    {
        //do stuff
        if(time % 1000 == 0 && time % 10000 !=0)
        {
            //do stuff every second
            int attackerTarget = rand() % networkUnderAttack.networkSize + 1;
            attacker.scheduleAttack(time + 100, -1, attackerTarget);// attackers attack
            for(int i = 0; i < sysadmin.infectedComputers.size(); i++)
            {
                networkUnderAttack.generateTarget(networkUnderAttack.network[sysadmin.infectedComputers[i]]);
                attacker.scheduleAttack (time + 100, sysadmin.infectedComputers[i], networkUnderAttack.generateTarget(networkUnderAttack.network[i]));
            }
            
        }
        else if(time % 1000 == 100)
        {
            // do stuff with latencies
        }
        else if(time % 10000 == 0)
        {
            //schedule fixes
            if(sysadmin.infectedComputers[0])
            {
                sysadmin.scheduleFix(time, sysadmin.infectedComputers[0]);
            }
        }
        time += 100;
    }
    return exitCode;
}

int main(int argc, const char * argv[]) {
    int numComputers = atoi(argv[1]);
    int attackPercent = atoi(argv[2]);
    int detectPercent = atoi(argv[3]);
    int result = simulateAttack(numComputers, attackPercent, detectPercent);
    return 0;
}
