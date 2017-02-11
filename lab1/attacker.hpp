//
//  attacker.hpp
//  lab1
//
//  Created by Ben Patient on 2/9/17.
//  Copyright © 2017 Ben Patient. All rights reserved.
//

#ifndef attacker_hpp
#define attacker_hpp

#include <stdio.h>

class Attacker
{
public:
    Attacker();
    Attacker(int rate);
    void attack(class Network network, int source, int target); // generates event to notify sysAdmin
    void scheduleAttack(class EventQueue x, unsigned long long int time, int source, int target);
    int successRate;
    bool succesfulAttack();
//private:
};

#endif /* attacker_hpp */
