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

using namespace std;

int simulateAttack(int numComputers, int attackPercent, int detectPercent)
{
    int exitCode;
    double time = 0; //time in ms
    double maxTime = 8640000000;
    Network networkUnderAttack = Network(numComputers);
    while( (networkUnderAttack.compromised != true) || (time < maxTime) ) // add exit for 100% fixed network
    {
        
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
