#ifndef DESTINATION_H
#define DESTINATION_H

#include "Positie.h"
#include "main.h"

class Destination : public Positie
{
    public:
                Destination();
                Destination(bool g, double x, double y, double corner);
        void    toggleGrab();
        bool    grabbed() const;
        void    setGrabbed(bool);

    protected:
    private:
        bool    grab;
};

#endif // DESTINATION_H
