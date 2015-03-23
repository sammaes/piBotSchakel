#ifndef SERVER_H
#define SERVER_H

//#include <thread>
//#include <mutex>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <iostream>
#include <csignal>
#include <unistd.h>
#include <string.h>
#include "Package.h"
#include "Buffer.h"

class Server
{
    public:
        void set_port(int port);
        void set_up();
        void listen();
        int teller;
    protected:
    private:
        int sockfd,n;
        struct sockaddr_in serveraddr,clientaddr;
        socklen_t len;
        int udp_port;
        Package package;
        Udp_package udp_package;
};
extern void server();
#endif // SERVER_H
