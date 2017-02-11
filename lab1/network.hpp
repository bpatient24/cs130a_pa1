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

using namespace std;

//COMPUTER DECLARATIONS *************************************************************************************
class Computer
{
    friend class Network;
public:
    //member functions
    void compromise();      //sets compromised to true.
    void fix();             //sets compromise to false.
    Computer();
    Computer(int location);
private:
    int target;
    bool compromised;
    int location;
};

//SYSADMIN DECLARATIONS *************************************************************************************
class SysAdmin
{
    friend class IDS;
    friend class Network;
public:
    SysAdmin();
    void fix(int time, int target);
    void processAlert();// TODO process the notify event
private:
    vector<int> infectedComputers; // array of indexes for infected computers
    void scheduleFix(int time, int target);  //Schedule a computer to be fixed. It can be compromised again.
};

//IDS DECLARATIONS *************************************************************************************/
class IDS
{
public:
    IDS();
    IDS(int rate);
    void notify(int attacker, int victim); // generates event to notify sysAdmin
private:
    int detectRate;
    bool detectedAttack(int rate);
};

//NETWORK DECLARATIONS *************************************************************************************
class Network: public Computer, public IDS, public SysAdmin
{
    friend class Computer;
public:
    Network();
    Network(int size); //initializes network of computers with the halfway point seperating left/right
    bool compromised;
    vector<Computer> network;
private:
    int networkSize;
    int percentCompromised;
    void generateTarget(Computer x); //get random int for target
    
};


#endif /* network_hpp */
