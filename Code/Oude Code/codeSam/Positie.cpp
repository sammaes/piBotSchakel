#include "Positie.h"

Positie::Positie()
{
    this->newPosition(0,0,0);
}

Positie::Positie(double newX, double newY, double cor)
{
    this->newPosition(newX,newY,cor);
}

bool Positie::operator==(const Positie &rhs) const
{
    return this->helperEqualOperator(rhs);
}

bool Positie::operator!=(const Positie &rhs) const
{
    return (!this->helperEqualOperator(rhs));
}

bool Positie::helperEqualOperator(const Positie &rhs) const
{
    return ((this->getX() == rhs.getX()) && (this->getY() == rhs.getY()) && (this->getAngle() == rhs.getAngle()));
}

void Positie::newPosition(double x,double y,double ang)
{
    this->setX(x);
    this->setY(y);
    this->setAngle(ang);
}

double Positie::getX() const
{
    return this->x;
}

void Positie::setX(double val)
{
    this->x = val;
}

double Positie::getY() const
{
    return this->y;
}

void Positie::setY(double val)
{
    this->y = val;
}

double Positie::getAngle() const
{
    return this->angle;
}

void Positie::setAngle(double ang)
{
    this->angle = ang;
}
