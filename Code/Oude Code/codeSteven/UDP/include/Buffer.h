#ifndef BUFFER_H
#define BUFFER_H

//#include <thread>
#include <iostream>
#include "Package.h"
#include "Server.h"


class Buffer
{

    public:
        static Package get_package();
        void set_package(Udp_package dp_package, int nr);
    protected:
    private:
        static Package package;
};

#endif // BUFFER_H
