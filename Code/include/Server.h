#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <cstring>
#include <functional>

#define STANDAARDGROEP 'b'
#define STANDAARDPOORT 3200

#include "Package.h"

class Server
{
    public:
			 	 	 	Server(int port, char c);
			 	 	 	Server();
        void 			setup();
        void 			listen();
        void 			setPoort(int port);
        void 			setGroep(char c);
        char 			getGroep();
        Info 			getInfo();
        bool 			dataValid();

    private:
        int 			sockfd;
        int 			udp_port;
        Info 			info;
        char 			groep;
        struct 			sockaddr_in serveraddr;
        struct 			sockaddr_in clientaddr;
        Udp_package 	pakket;
};
#endif // SERVER_H
