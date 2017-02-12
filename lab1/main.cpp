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
    attacker.scheduleAttack(*priorityQueue, 1000, -1, rand() % networkUnderAttack.networkSize + 1);
    
    while(!exit)
    {
        priorityQueue->deleteMin(nextEvent);
        globaltime += nextEvent.time;
        if(nextEvent.isFix)
        {
            //dipatch fix event
            //cout << "TRIED TO DISPATCH FIX" << endl;
            sysadmin.fix(networkUnderAttack, nextEvent.target);
            fixMessage(globaltime, nextEvent.target);
        }
        else
        {
            // dispatch attack event
            //cout << "TRIED TO DISPATCH ATTACK" << endl;
            
            if(nextEvent.source == -1)
            {
                int attackerTarget = rand() % networkUnderAttack.networkSize + 1;
                attacker.attack(networkUnderAttack, -1, attackerTarget);
                ids.notify(networkUnderAttack, globaltime, nextEvent.source, attackerTarget);
                for(int i = 0; i < networkUnderAttack.networkSize - 1; i++)
                {
                    if(networkUnderAttack.network[i].compromised == true)
                    {
                        int target = rand() % networkUnderAttack.networkSize + 1;
                        attacker.scheduleAttack(*priorityQueue, 1000, i, target);
                    }
                }
            }
            else if(nextEvent.source > -1)
            {
                int target = rand() % networkUnderAttack.networkSize + 1;
                attacker.attack(networkUnderAttack, nextEvent.source, target);
                attackMessage(globaltime, nextEvent.source, target);
                ids.notify(networkUnderAttack, globaltime, nextEvent.source, target);
            }
        }
    }
    if(networkUnderAttack.compromised() == true)
    {
        exitCode= 2;
        exit = true;
    }
    else if(!(firstLoop) && (networkUnderAttack.percentCompromised == 0))
    {
        exitCode = 1;
        exit = true;
    }
    else if(globaltime > maxTime)
    {
        exitCode = 3;
        exit = true;
    }
    cout << "GLOBAL TIME = " << globaltime << endl;
    globaltime += 100;
    firstLoop = false;
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


