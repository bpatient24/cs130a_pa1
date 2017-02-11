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
    int target;
private:
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
    void fix(class Network network, int target);
    void processNotify(class Network network, int attacker, int victim);//process the notify event
    vector<int> infectedComputers;
    void scheduleFix(class EventQueue x,unsigned long long int time, int target);  //Schedule a computer to be fixed. It can be compromised again.
private:
    void addInfected(int networkIndex);
    void removeInfected(int networkIndex);
};

//IDS DECLARATIONS *************************************************************************************/
class IDS //: public SysAdmin
{
public:
    IDS();
    IDS(int rate);
    void notify(class Network myNetwork, class SysAdmin sys, int attacker, int victim); // generates event to notify sysAdmin
private:
    int detectRate;
    bool detectedAttack(class Network myNetwork);
};


//NETWORK DECLARATIONS *************************************************************************************
class Network: public Computer, public IDS
{
    friend class Computer;
    friend class SysAdmin;
    friend class IDS;
public:
    Network();
    Network(int size);   //initializes network of computers with the halfway point seperating left/right
    bool compromised();  //checks if the network has be taken over
    vector<Computer> network;
    void fixComputer(int index);
    int percentCompromised;
    int getNetworkSize();
    int networkSize;
    int dividerIndex;
    void generateTarget(Computer x); //get random int for target
//private:
    
};


#endif /* network_hpp */
