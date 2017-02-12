//
//  sysadmin.h
//  lab1
//
//  Created by Ben Patient on 2/11/17.
//  Copyright © 2017 Ben Patient. All rights reserved.
//

#ifndef sysadmin_h
#define sysadmin_h

class SysAdmin
{
public:
    SysAdmin()
    {
        cout << "SysAdmin Initialized" << endl;
    }
    
    void fix(Network network, int fixTarget)
    {
        //add fix event and remove from infected list
        network.fixComputer(fixTarget);
    }
    
    void processNotify(int time, int attacker, int victim) //process the notify event
    {
        notifyMessage(time, attacker, victim);
    }
    
    void scheduleFix(EventQueue<Event> z, long time, int target) //Schedule a computer to be fixed. It can be compromised again.
    {
        Event fix;
        fix = Event(true, time, -2, target);
        z.addEvent(fix);
    }
    //private:
    
};


#endif /* sysadmin_h */
