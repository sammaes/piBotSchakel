#ifndef ROBOT_H
#define ROBOT_H

#include "Positie.h"
#include "Destination.h"

class Robot
{
    public:
                        Robot(int angle,int xrobot, int yrobot, int xblikje, int yblikje, int xgarage, int ygarage, bool grab);
                        Robot() {}
        bool            grabbedItem();
        void            setGrabbedItem(bool val);
        Destination     getDestination();
        void            setDestination(Destination val);
        Positie         getPositieRobot();
        void            setPositieRobot(Positie val);
        void            setPositieRobot(int x, int y, int angle);
        Positie         getPositieBlikje();
        void            setPositieBlikje(Positie val);
        void            setPositieBlikje(int x, int y);
        Positie         getPositieGarage();
        void            setPositieGarage(Positie val);
        void            setPositieGarage(int x, int y);
        void            berekenRoute();
        void            stop();
        void            grab();
        void			print();

    protected:
    private:
        int      angle;
        bool        grabbed;
        Positie     posRobot;
        Positie		posBlikje;
        Positie		posGarage;

         /* Driving */
        void        vooruit(double speed);
        void        achteruit(double speed);
        void        turnClock(double corner);
        void        turnAntiClock(double corner);

};

#endif // ROBOT_H
