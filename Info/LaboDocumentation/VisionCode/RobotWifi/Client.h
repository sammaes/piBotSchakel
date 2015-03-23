//
//  Client.h
//  RobotCirkelDetector
//
//  Created by Jeroen Provoost on 21/03/14.
//  Copyright (c) 2014 Jeroen Provoost. All rights reserved.
//

#ifndef __RobotCirkelDetector__Client__
#define __RobotCirkelDetector__Client__

#include <iostream>
#include <iomanip>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include "Package.h"

#define groepA "192.168.1.125"
#define groepB "192.168.1.13"


class Client {
    	int sockfd,n;
    	int sockGroepB;
    	struct sockaddr_in servaddr_a;
	struct sockaddr_in servaddr_GroepB;
public:
    	void init();
	void initB();
    	void close_socket();
 	void close_socketB();
    	void send(Udp_package udp_package);
    	void sendB(Udp_package udp_package);
};

#endif /* defined(__RobotCirkelDetector__Client__) */
