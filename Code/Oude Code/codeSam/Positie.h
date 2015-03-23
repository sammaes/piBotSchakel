#ifndef POSITIE_H
#define POSITIE_H

#include "main.h"

class Positie
{
    public:
                            Positie();
                            Positie(double newX, double newY, double cor);
                double      getX() const;
                void        setX(double val);
                double      getY() const;
                void        setY(double val);
                double      getAngle() const;
                void        setAngle(double ang);
                void        newPosition(double newX,double newY, double cor);
                bool        operator==(const Positie &rhs) const;
                bool        operator!=(const Positie &rhs) const;

    protected:
    private:
                double      x;
                double      y;
                double      angle;
                bool        helperEqualOperator(const Positie &rhs) const;
};

#endif // POSITIE_H
