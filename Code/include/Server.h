#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <cstring>
#include <functional>

#include "debug.h"
#include "Package.h"

#define STANDAARDGROEP 'b'
#define STANDAARDPOORT 3200

class Server
{
    public:
						~Server();
			 	 	 	Server(int port = STANDAARDPOORT, char c = STANDAARDGROEP);

        void 			setup();
        void 			listen();
        void 			setPoort(int port);
        void 			setGroep(char c);
        char 			getGroep();
        Info 			getInfoEigen();
        Info			getInfoObstakel();
        bool 			dataEigenValid();
        bool			dataObstakelValid();

    private:
        int 			sockfd;
        int 			udp_port;
        Info 			infoEigen;
        Info			infoObstakel;
        char 			groep;
        struct 			sockaddr_in serveraddr;
        struct 			sockaddr_in clientaddr;
        Udp_package 	pakket;
};
#endif // SERVER_H
