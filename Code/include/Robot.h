#ifndef ROBOT_H
#define ROBOT_H

#include 				"Positie.h"

class Robot
{
    public:
                        Robot();
        Positie         getPositieRobot();
        void            setPositieRobot(Positie val);
        void            setPositieRobot(int x, int y, int angle);
        Positie         getPositieBlikje();
        void            setPositieBlikje(Positie val);
        void            setPositieBlikje(int x, int y);
        Positie         getPositieGarage();
        void            setPositieGarage(Positie val);
        void            setPositieGarage(int x, int y);
        void            stop();
        void            grab();
        void			print();

        /* Driving */
       void       		vooruit(double speed);
       void        		achteruit(double speed);
       void        		turnClock(double corner);
       void        		turnAntiClock(double corner);

    private:
        int      		angle;
        Positie     	posRobot;
        Positie			posBlikje;
        Positie			posGarage;
};

#endif // ROBOT_H
