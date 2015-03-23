#ifndef ROBOT_H
#define ROBOT_H

#include "Positie.h"
#include "Destination.h"
#include "main.h"

class Robot
{
    public:
                        Robot(bool gi, Destination d, Positie r);
        bool            grabbedItem() const;
        void            setGrabbedItem(bool val);
        Destination     getDestination() const;
        void            setDestination(Destination val);
        Positie         getPositie() const;
        void            setPositie(Positie val);
        void            berekenRoute();
        void            stop();
        void            grab();

    protected:
    private:
        double      angle;
        bool        grabbed;
        Destination destination;
        Positie     posRobot;

         /* Driving */
        void        vooruit(double speed);
        void        achteruit(double speed);
        void        turnClock(double corner);
        void        turnAntiClock(double corner);

};

#endif // ROBOT_H
