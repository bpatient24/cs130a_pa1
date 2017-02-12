//
//  network.h
//  lab1
//
//  Created by Ben Patient on 2/11/17.
//  Copyright © 2017 Ben Patient. All rights reserved.
//

#ifndef network_h
#define network_h

#include "computer.h"

class Network
{
public:
    Network()
    {
        network = new Computer[100];
        cout << "Network default constructor" << endl;
    }
    Network(int size)   //initializes network of computers with the halfway point seperating left/right
    {
        network = new Computer[size];
        
        if(size % 2 == 1)
        {
            dividerIndex = size / 2 + 1;
        }
        else
        {
            dividerIndex = size / 2;
        }
        networkSize = size;
        percentCompromised = 0;
        cout << "Network Properly Initialized" << endl;
    }
    
    bool compromised() //checks if the network has be taken over
    {
        return percentCompromised > 50;
    }
    Computer *network;
    void fixComputer(int index)
    {
        network[index].fix();
    }
    int percentCompromised;
    int getNetworkSize();
    int networkSize;
    int dividerIndex;
    void generateTarget(Computer x) //get random int for target
    {
        x.target = rand() % networkSize + 1;
    }
    //private:
};

#endif /* network_h */
