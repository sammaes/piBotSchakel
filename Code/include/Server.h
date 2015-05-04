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
						/**
						 * Destructor van Server
						 */
						~Server();
						/**
						 * Constructor van Server
						 * @param port UDP poort
						 * @param c groepsletter
						 */
			 	 	 	Server(int port = STANDAARDPOORT, char c = STANDAARDGROEP);

		/**
		 *
		 */
        void 			setup();
        /**
         *
         */
        void 			listen();
        /**
         *
         * @param port
         */
        void 			setPoort(int port);
        /**
         *
         * @param c
         */
        void 			setGroep(char c);
        /**
         *
         * @return
         */
        char 			getGroep();
        /**
         *
         * @return
         */
        Info 			getInfo();
        /**
         *
         * @return
         */
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
