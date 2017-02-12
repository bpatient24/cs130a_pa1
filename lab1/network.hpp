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
#include <vector>
#include "event.h"
#include "eventQueue.h"

using namespace std;

//SYSADMIN DECLARATIONS *************************************************************************************
class SysAdmin
{
public:
    SysAdmin();
    void fix(class Network network,int target);
    void processNotify(int time, int attacker, int victim);//process the notify event
    void scheduleFix(EventQueue<Event> z, long time, int target);  //Schedule a computer to be fixed. It can be compromised again.
    //private:
    
};

//COMPUTER DECLARATIONS *************************************************************************************
class Computer
{
public:
    //member functions
    void compromise();      //sets compromised to true.
    void fix();             //sets compromise to false.
    Computer();
    Computer(int location);
    int target;
    bool compromised;
    int location;
//private:

};

//IDS DECLARATIONS *************************************************************************************/
class IDS //: public SysAdmin
{
public:
    IDS();
    IDS(int rate);
    void notify(class Network myNetwork, int time, int attacker, int victim); // generates event to notify sysAdmin
    int detectRate;
    bool detectedAttack();
//private:
};


//NETWORK DECLARATIONS *************************************************************************************
class Network
{
public:
    Network();
    Network(int size);   //initializes network of computers with the halfway point seperating left/right
    bool compromised();  //checks if the network has be taken over
    Computer *network;
    void fixComputer(int index);
    int percentCompromised;
    int getNetworkSize();
    int networkSize;
    int dividerIndex;
    void generateTarget(Computer x); //get random int for target
//private:
    
};

#endif /* network_hpp */
