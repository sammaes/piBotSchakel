#include "Server.h"

Server::~Server()
{
	//TODO: INCLUDE voor close() in ~Server
	//close(sockfd);
}

Server::Server(int port, char c) {
	this->setGroep(c);
	this->setPoort(port);
	this->setup();
}

void Server::setup() {
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(udp_port);

	if (bind(sockfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) == -1) {
		std::cerr << "Server:\tERROR: Error binding UDP socket" << std::endl;
		return;
	}
	#ifdef DEBUGSERVER
		std::cout << "Server:\t Server is ready" << std::endl;
	#endif //DEBUGSERVER
}

void Server::listen() {
	socklen_t len;

	#ifdef DEBUGSERVER
		std::cout << "Server:\t Waiting for package" << std::endl;
	#endif //DEBUGSERVER

	len = sizeof(clientaddr);

	if (recvfrom(sockfd, &pakket, sizeof(struct Udp_package), 0,(struct sockaddr *) &clientaddr, &len) > 0) {

		if (this->getGroep() != 'b')
			info = pakket.info_a;
		else
			info = pakket.info_b;

		#ifdef DEBUGSERVER
			if (this->dataValid())
			{
				std::cout << "=================" << this->getGroep() << "=================" << std::endl;
				std::cout << "Server: UDP package received" << std::endl;
				std::cout << "Robotx:" << info.robotx << std::endl;
				std::cout << "roboty:" << info.roboty << std::endl;
				std::cout << "robothoek:" << info.robothoek << std::endl;
				std::cout << "blikx:" << info.blikx << std::endl;
				std::cout << "bliky:" << info.bliky << std::endl;
				std::cout << "garagex:" << info.garagex << std::endl;
				std::cout << "garagey:" << info.garagey << std::endl;
				std::cout << "===================================" << std::endl;
			}
			else
				std::cout << "Server: Ingelezen data niet valid" << std::endl;
		#endif //DEBUGSERVER
	}
}

// Vanaf dat een van de ontvangen gelijk zijn aan -1 is data in info niet meer valid.
bool Server::dataValid() {
	return !((info.robotx == -1) || (info.roboty == -1) || (info.robothoek == -1) || (info.blikx == -1) || (info.bliky == -1) || (info.garagex == -1) || (info.garagey == -1));
}

Info Server::getInfo() {
	return this->info;
}

void Server::setGroep(char c) {
	this->groep = tolower(c);
}

char Server::getGroep() {
	return this->groep;
}

void Server::setPoort(int port) {
	udp_port = port;
}

