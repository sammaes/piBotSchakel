#include "include/Server.h"
#include <functional>
#define ID 2
#define UDP_PORT 3200
#define DEBUG 1

using namespace std;

void Server::set_port(int port){
    udp_port = port;
}

void Server::set_up(){
    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    memset(&serveraddr,0,sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(udp_port);
    auto test = bind(sockfd,(struct sockaddr *)&serveraddr, sizeof(serveraddr));
    //auto: type van variable wordt automatisch bepaald door functie
    #ifdef DEBUG
        cout << "Server is ready\n" <<test<<"\n";
    #endif
}

void Server::listen(){
    #ifdef DEBUG
        cout << "Waiting for package\n";
    #endif
    len = sizeof(clientaddr);
    n = recvfrom(sockfd,&udp_package,sizeof(Udp_package), 0, (struct sockaddr *)&clientaddr,&len);

    Buffer p;
    p.set_package(udp_package,teller++);
    #ifdef DEBUG
        p.get_package();
    #endif
}

void server(){
    Server s;
    s.teller=0;
    s.set_port(UDP_PORT);
    s.set_up();

    for(;;){
        s.listen();
    }
}

