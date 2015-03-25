#ifndef POSITIE_H
#define POSITIE_H

#include "debug.h"

class Positie
{
    public:
                            Positie();
                            Positie(int newX, int newY, int cor);

                int		    getX() const;
                void        setX(int val);
                int      	getY() const;
                void        setY(int val);
                int      	getAngle() const;
                void        setAngle(int ang);
                void        newPosition(int newX,int newY, int cor);
                bool        operator==(const Positie &rhs) const;
                bool        operator!=(const Positie &rhs) const;

                void		print();
    private:
                int      	x;
                int      	y;
                int      	angle;
                bool        helperEqualOperator(const Positie &rhs) const;
};

#endif // POSITIE_H
