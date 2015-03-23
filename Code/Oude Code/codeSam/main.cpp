#include <iostream>
#include "Destination.h"
#include "Positie.h"
#include "Robot.h"
#include "UDPclient.h"
#include "main.h"

#define TEST2

int main()
{
    bool grab = true;   // Zegt dat eerste keer de grijper moet grijpen bij het arriveren bij eerste destination

    #ifdef DUMMY
        #ifdef TEST1
            Destination d(grab,8.0,5.0,135.0);       // Komt normaal via UDP
            Positie p(2.0,2.0,50.0);                // Deze ook...
        #endif // TEST1
        #ifdef TEST2
            Destination d(grab,8.0,5.0,135.0);       // Komt normaal via UDP
            Positie p(2.0,2.0,285.0);                // Deze ook...
        #endif // TEST2
    #else
        // hier komt positie en destination via udp
        UDPclient udp;
    #endif // DUMMY

    Robot r2d2(!grab,d,p);  // !grab: omdat de robot item nog niet gegrabed heeft

    while (/*!r2d2.grabbedItem()*/r2d2.getPositie() != r2d2.getDestination())     // Enkel naar blikje rijden
    {
        r2d2.setPositie(p);
        r2d2.setDestination(d);
        r2d2.berekenRoute();        // r2d2 beslist welke richting hij moet rijden en doet dit daarna
        #ifdef DUMMY
            p.newPosition(p.getX()+2,p.getY()+1,135.0); // enkel in test
        #endif // DUMMY
    }
    r2d2.grab();
    r2d2.stop();

    return 0;
}
