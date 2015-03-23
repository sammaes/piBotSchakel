#include "Robot.h"
#ifdef DEBUG
    #include <iostream>
#endif // DEBUG

Robot::Robot(bool gi, Destination d, Positie r)
{
    this->setGrabbedItem(gi);
    this->setDestination(d);
    this->setPositie(r);
}

bool Robot::grabbedItem() const
{
    return this->grabbed;
}

void Robot::setGrabbedItem(bool val)
{
    this->grabbed = val;
}

Destination Robot::getDestination() const
{
    return this->destination;
}

void Robot::setDestination(Destination val)
{
    this->destination = val;
}

Positie Robot::getPositie() const
{
    return this->posRobot;
}

void Robot::setPositie(Positie val)
{
    this->posRobot = val;
}

void Robot::berekenRoute()
{
    double cornerDest  = this->destination.getAngle();
    double cornerRobot = this->posRobot.getAngle();

    #ifdef DEBUG
        std::cout << "Berekenen van de route" << std::endl;
        std::cout << "\tPositie::    x:" << this->posRobot.getX() << " y:" << this->posRobot.getY() << " angle:" << cornerRobot << std::endl;
        std::cout << "\tBestemming:: x:" << this->getDestination().getX() << " y:" << this->getDestination().getY() << " angle:" << cornerDest << std::endl;
    #endif // DEBUG

    /* Draaien */
    if (cornerDest < cornerRobot)
    {
        this->turnClock(cornerRobot - cornerDest);
    }
    else if (cornerDest > cornerRobot)
    {
        this->turnAntiClock(cornerDest - cornerRobot);
    }
    else // Niet nodig om te draaien
    {
        #ifdef DUMMY
            this->vooruit(100.0);
        #else
            // beslis waar robot naartoe moet met welke snelheid
        #endif // DUMMY

    }

}

/* Driving */

void Robot::vooruit(double speed)
{
    #ifdef DEBUG
        std::cout << "r2d2 rijdt vooruit met snelheid:" << speed << std::endl;
    #endif // DEBUG
}

void Robot::achteruit(double speed)
{
    #ifdef DEBUG
        std::cout << "r2d2 rijdt achteruit met snelheid:" << speed << std::endl;
    #endif // DEBUG
}

void Robot::turnClock(double corner)
{
    #ifdef DEBUG
        std::cout << "r2d2 draait clockwise over " << corner << " graden" << std::endl;
    #endif // DEBUG
}

void Robot::turnAntiClock(double corner)
{
    #ifdef DEBUG
        std::cout << "r2d2 draait anticlockwise over " << corner << " graden" << std::endl;
    #endif // DEBUG
}

void Robot::stop()
{
    #ifdef DEBUG
        std::cout << "r2d2 stopt" << std::endl;
    #endif // DEBUG
}

void Robot::grab()
{
    #ifdef DEBUG
        std::cout << "r2d2 neemt blikje vast" << std::endl;
    #endif // DEBUG
    this->getDestination().toggleGrab();
}
