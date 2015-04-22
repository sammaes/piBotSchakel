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
		{
			infoEigen = pakket.info_a;
			infoObstakel = pakket.info_b;
		}
		else
		{
			infoEigen = pakket.info_b;
			infoObstakel = pakket.info_a;
		}

		#ifdef DEBUGSERVER
			if (this->dataValid())
			{
				std::cout << "=================" << this->getGroep() << "=================" << std::endl;
				std::cout << "Server: UDP package eigen received" << std::endl;
				std::cout << "Robotx:" << infoEigen.robotx << std::endl;
				std::cout << "roboty:" << infoEigen.roboty << std::endl;
				std::cout << "robothoek:" << infoEigen.robothoek << std::endl;
				std::cout << "blikx:" << infoEigen.blikx << std::endl;
				std::cout << "bliky:" << infoEigen.bliky << std::endl;
				std::cout << "garagex:" << infoEigen.garagex << std::endl;
				std::cout << "garagey:" << infoEigen.garagey << std::endl;
				std::cout << "===================================" << std::endl;
			}
			else
				std::cout << "Server: Ingelezen data niet valid" << std::endl;
		#endif //DEBUGSERVER
	}
}

// Vanaf dat een van de ontvangen gelijk zijn aan -1 is data in info niet meer valid.
bool Server::dataValid() {
	return !((infoEigen.robotx == -1) || (infoEigen.roboty == -1) || (infoEigen.robothoek == -1) || (infoEigen.blikx == -1) ||
			(infoEigen.bliky == -1) || (infoEigen.garagex == -1) || (infoEigen.garagey == -1) || (infoObstakel.robotx == -1) ||
			(infoObstakel.roboty == -1) || (infoObstakel.robothoek == -1) || (infoObstakel.blikx == -1) ||
			(infoObstakel.bliky == -1) || (infoObstakel.garagex == -1) || (infoObstakel.garagey == -1));
}

Info Server::getInfoEigen() {
	return this->infoEigen;
}

Info Server::getInfoObstakel() {
	return this->infoObstakel;
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

