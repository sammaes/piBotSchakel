#include "Positie.h"

Positie::Positie()
{
    this->newPosition(0,0,0);
}

Positie::Positie(int newX, int newY, int cor)
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

void Positie::newPosition(int x,int y,int ang)
{
    this->setX(x);
    this->setY(y);
    this->setAngle(ang);
}

int Positie::getX() const
{
    return this->x;
}

void Positie::setX(int val)
{
    this->x = val;
}

int Positie::getY() const
{
    return this->y;
}

void Positie::setY(int val)
{
    this->y = val;
}

int Positie::getAngle() const
{
    return this->angle;
}

void Positie::setAngle(int ang)
{
    this->angle = ang;
}
