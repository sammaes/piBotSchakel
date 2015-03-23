#include "Destination.h"
#ifdef DEBUG
    #include <iostream>
#endif // DEBUG


Destination::Destination() : Positie()
{
    this->setGrabbed(false);
}

Destination::Destination(bool g, double x, double y, double corner) : Positie(x,y,corner)
{
    this->setGrabbed(g);
}

void Destination::toggleGrab()
{
    this->setGrabbed(!this->grabbed());
    #ifdef DEBUG
        std::cout << "grab:" << this->grabbed() << std::endl;
    #endif // DEBUG
}

bool Destination::grabbed() const
{
    return this->grab;
}

void Destination::setGrabbed(bool g)
{
    this->grab = g;
}
