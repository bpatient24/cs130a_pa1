//
//  computer.h
//  lab1
//
//  Created by Ben Patient on 2/11/17.
//  Copyright © 2017 Ben Patient. All rights reserved.
//

#ifndef computer_h
#define computer_h

class Computer
{
public:
    //member functions
    void compromise()      //sets compromised to true.
    {
        compromised = true;
        
    }
    void fix()           //sets compromise to false.
    {
        compromised = false;
        
    }
    Computer()
    {
        compromised = false;
        location = 0;
        target = 1;
    }
    Computer(int location)
    {
        compromised = false;
        location = location;
        target = 1;
    }
    int target;
    bool compromised;
    int location;

    
};

#endif /* computer_h */
