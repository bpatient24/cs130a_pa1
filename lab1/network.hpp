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
    void fix(class Network network, int time, int target);
    void processNotify(class Network network, int attacker, int victim);//process the notify event
private:
    void scheduleFix(int time, int target);  //Schedule a computer to be fixed. It can be compromised again.
    vector<int> infectedComputers; // array of indexes for infected computers
    void addInfected(int networkIndex);
    void removeInfected(int networkIndex);
};

//IDS DECLARATIONS *************************************************************************************/
class IDS: public SysAdmin
{
public:
    IDS();
    IDS(int rate);
    void notify(class Network myNetwork, int attacker, int victim); // generates event to notify sysAdmin
private:
    int detectRate;
    bool detectedAttack(class Network myNetwork);
};


//NETWORK DECLARATIONS *************************************************************************************
class Network: public Computer, public SysAdmin , public IDS
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

private:
    int networkSize;
    int dividerIndex; 
    int percentCompromised;
    void generateTarget(Computer x); //get random int for target
};


#endif /* network_hpp */
