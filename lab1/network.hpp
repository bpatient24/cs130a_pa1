//
//  network.hpp
//  lab1
//
//  Created by Ben Patient on 2/9/17.
//  Copyright © 2017 Ben Patient. All rights reserved.
//

#ifndef network_hpp
#define network_hpp

#include <stdio.h>

class Computer
{
public:
    //member functions
    Computer(int location); //constructor
    void compromise(Computer x);  //sets compromised to true.
    void fix(Computer x);            //sets compromise to false.
    
private:
    bool compromised;
    int target;
    int location;
    void generateTarget(); //get random int for targer
};


class IDS
{
public:
    void computerAttacked(int attacker, int victim); // generates event to notify sysAdmin
    
    void notify(int time, int target);  // The sysadmin will be notified by the IDS that an attack was detected. This gives the sysadmin both the source and the target via the attack object. The sysadmin will schedule fixes for both. The sysadmin can schedule fixes 10 seconds apart, and it takes 10 seconds from notification to first fix.

private:
    int detectionRate;
};


class Network: public Computer, public IDS
{
public:
    Network(int size);  //initializes network of computers with the halfway point seperating left/right
private:
    int networkSize;
    int percentCompromised;
    
};


#endif /* network_hpp */
