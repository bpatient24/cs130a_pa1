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
//#include "network.h"

using namespace std;

// -1 = attacker ; -2  = sysadmin
int simulateAttack(int numComputers, int attackPercent, int detectPercent)
{
    int exitCode;
    bool exit;
    unsigned long long int globaltime = 0; //time in ms
    unsigned long long int maxTime = 8640000000;
    bool firstLoop = true;
    Event nextEvent;
    Network networkUnderAttack = Network(numComputers);
    SysAdmin sysadmin = SysAdmin();
    IDS ids = IDS(detectPercent);
    Attacker attacker = Attacker(attackPercent);
    EventQueue<Event> *priorityQueue = new EventQueue<Event>();
    //Event fix;
    //fix = Event(true, 5000, -2, 5);
    //priorityQueue->addEvent(fix);
    //sysadmin.scheduleFix(*priorityQueue, 500, 4);
    //cout << "FIX TIME IS: " << fix.time << endl;
    //cout << "TIME IS: " << priorityQueue->returnNextEventTime() << endl;
    //cout << "Heap Size is: " << priorityQueue->heapSize << endl;
    //priorityQueue->deleteMin(nextEvent);
    attacker.scheduleAttack(*priorityQueue, 100, -1, rand() % networkUnderAttack.networkSize + 1);
    
    while(!exit)
    {
        //do stuff
        if(globaltime % 1000 == 0 && globaltime % 10000 != 0)
        {
            //cout << "Reached Case 1" << endl;
            //do stuff every second
            int attackerTarget = rand() % networkUnderAttack.networkSize + 1;
            attacker.scheduleAttack(*priorityQueue, globaltime + 100, -1, attackerTarget);// attackers attack
            
            for(int i = 0; i < sysadmin.infectedComputers.size(); i++)
            {
                int target = rand() % networkUnderAttack.networkSize + 1;
                attacker.scheduleAttack(*priorityQueue, globaltime + 100, sysadmin.infectedComputers[i], target);
            }
            
            /*for(int i = 0; i < networkUnderAttack.networkSize; i++)
            {
                if(networkUnderAttack.network[i].compromised == true)
                {
                    cout << "HELLO" << endl;
                    networkUnderAttack.generateTarget(networkUnderAttack.network[i]);
                    attacker.scheduleAttack (*priorityQueue, globaltime + 100, i, networkUnderAttack.network[i].target);
                }
                //networkUnderAttack.generateTarget(networkUnderAttack.network[sysadmin.infectedComputers.at(i)]);
            }*/
        }
        else if(globaltime % 1000 == 100)
        {
            //cout << "Reached Case 2 at time " << globaltime << "TIMESTAMP: "  << priorityQueue[0].time << endl;
            // do stuff with latencies
            while(priorityQueue->returnNextEventTime() == globaltime)
            {
                priorityQueue->deleteMin(nextEvent);
                if(nextEvent.isFix)
                {
                    //dipatch fix event
                    //cout << "TRIED TO DISPATCH FIX" << endl;
                    sysadmin.fix(networkUnderAttack, nextEvent.target);
                    fixMessage(nextEvent.time, nextEvent.target);
                }
                else
                {
                    // dispatch attack event
                    //cout << "TRIED TO DISPATCH ATTACK" << endl;
                    attacker.attack(networkUnderAttack, nextEvent.source, nextEvent.target);
                    attackMessage(nextEvent.time, nextEvent.source, nextEvent.target);
                    ids.notify(networkUnderAttack, sysadmin, nextEvent.source, nextEvent.target);
                }
            }
        }
        else if(globaltime % 10000 == 0)
        {
            //cout << "Reached Case 3" << endl;
            //schedule fixes
            for(int i = 0; i < networkUnderAttack.networkSize; i++)
            {
                if(networkUnderAttack.network[i].compromised == true)
                {
                    sysadmin.scheduleFix(*priorityQueue, globaltime + 100, i);
                    break;
                }
                //networkUnderAttack.generateTarget(networkUnderAttack.network[sysadmin.infectedComputers.at(i)]);
            }
        }
        
        exit = (networkUnderAttack.compromised() == true) && (globaltime < maxTime) && ((firstLoop) || !(networkUnderAttack.percentCompromised == 0));
        firstLoop = false;
        
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
        //cout << "GLOBAL TIME = " << globaltime << endl;
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


