#ifndef ROBOT_H
#define ROBOT_H

#include				<string>
#include 				"debug.h"
#include 				"Positie.h"
#include				"Server.h"
#include				"robotcommand.h"
#include				"Hoek.h"
#include				"Average.h"

class Robot: public Server, public robotcommand, public Hoek
{
    public:
                        Robot(int udpPoort,string serialPoort, char groep);

        Positie         getPositieRobot();
        void            setPositieRobot(Positie val);
        void            setPositieRobot(int x, int y, int angle);
        Positie         getPositieBlikje();
        void            setPositieBlikje(Positie val);
        void            setPositieBlikje(int x, int y);
        Positie         getPositieGarage();
        void            setPositieGarage(Positie val);
        void            setPositieGarage(int x, int y);

        void			print();

        void			updatePosities();
        void			bepaalHoekBlikje();
        void			bepaalHoekGarage();
        void			bepaalAfstandBlikje();
        void			bepaalAfstandGarage();

    private:
        Positie     	posRobot;
        Positie			posBlikje;
        Positie			posGarage;
        Average 		avgposrobot;
        Average			avgposblikje;
        Average			avgposgarage;
};

#endif // ROBOT_H
