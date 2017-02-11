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
    bool exit;
    unsigned long long int globaltime = 0; //time in ms
    unsigned long long int maxTime = 8640000000;
    bool firstLoop = true;
    Network networkUnderAttack = Network(numComputers);
    SysAdmin sysadmin = SysAdmin();
    IDS ids = IDS(detectPercent);
    Attacker attacker = Attacker(attackPercent);
    EventQueue *priorityQueue = new EventQueue();
    while(!exit)
    {
        //do stuff
        if(globaltime % 1000 == 0 && globaltime % 10000 !=0)
        {
            cout << "Reached Case 1" << endl;
            //do stuff every second
            int attackerTarget = rand() % networkUnderAttack.networkSize + 1;
            attacker.scheduleAttack(*priorityQueue, globaltime + 100, -1, attackerTarget);// attackers attack
            for(int i = 0; i < sysadmin.infectedComputers.size(); i++)
            {
                networkUnderAttack.generateTarget(networkUnderAttack.network[sysadmin.infectedComputers.at(i)]);
                networkUnderAttack.generateTarget(networkUnderAttack.network[i]);
                attacker.scheduleAttack (*priorityQueue, globaltime + 100, sysadmin.infectedComputers.at(i), networkUnderAttack.network[i].target);
            }
        }
        else if(globaltime % 1000 == 100)
        {
            cout << "Reached Case 2" << endl;
            // do stuff with latencies
            while(priorityQueue[0].time == globaltime)
            {
                if(priorityQueue[0].isFix)
                {
                    //dipatch fix event
                    sysadmin.fix(networkUnderAttack, priorityQueue[0].target);
                    fixMessage(priorityQueue[0].time, priorityQueue[0].target);
                    priorityQueue->removeMin();
                }
                else
                {
                    // dispatch attack event
                    attacker.attack(networkUnderAttack, priorityQueue[0].source, priorityQueue[0].target);
                    attackMessage(priorityQueue[0].time, priorityQueue[0].source, priorityQueue[0].target);
                    ids.notify(networkUnderAttack, sysadmin, priorityQueue[0].source, priorityQueue[0].target);
                    priorityQueue->removeMin();
                }
            }
        }
        else if(globaltime % 10000 == 0)
        {
            
            //schedule fixes
            try{
                sysadmin.scheduleFix(*priorityQueue, globaltime + 100, sysadmin.infectedComputers.at(0));
            }
            catch (out_of_range){
                sysadmin.infectedComputers.resize(10);
                cout << "SOMETHING" << endl;
            }
            /*if((sysadmin.infectedComputers.empty()))
            {
                cout << sysadmin.infectedComputers.at(0) << endl;
                sysadmin.scheduleFix(*priorityQueue, globaltime + 100, sysadmin.infectedComputers.at(0));
            }*/
        }
        
        exit = (networkUnderAttack.compromised() == true) && (globaltime < maxTime) && ((firstLoop) || !(networkUnderAttack.percentCompromised == 0));
        
        if(exit)
        {
            if(networkUnderAttack.compromised() != true)
            {
                exitCode= 1;
            }
            else if((firstLoop) || !(networkUnderAttack.percentCompromised == 0))
            {
                exitCode = 2;
            }
            else if(globaltime < maxTime)
            {
                exitCode = 3;
            }
        }
        //cout << globaltime << endl;
        globaltime += 100;
    }
    return exitCode;
}

int main(int argc, const char * argv[]) {
    //int numComputers = atoi(argv[1]);
    //int attackPercent = atoi(argv[2]);
    //int detectPercent = atoi(argv[3]);
    //int result = simulateAttack(numComputers, attackPercent, detectPercent);
    int result = simulateAttack(100, 100, 1);
    endMessage(result);
    return 1;
}


