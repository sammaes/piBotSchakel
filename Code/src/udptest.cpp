//============================================================================
// Name        : UDP.cpp
// Author      : Sam
// Version     :
// Copyright   : copyright
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <csignal>
#include <cstdlib>
#include <math.h>

#include "Server.h"
#include "Robot.h"
#include "Hoek.h"
#include "robotcommand.h"

Robot t;

robotcommand* NieuwCommand;

void stopRobot(int signum) {
#ifdef DEBUG
	std::cout << "\nSignaal (" << signum << ") ontvangen" << std::endl;
#endif
	NieuwCommand->stop();

	exit(signum);
}

int main() {

	signal(SIGQUIT, stopRobot);
	signal(SIGINT, stopRobot);  // CTRL+C ingedrukt
	signal(SIGHUP, stopRobot);  // Terminal disconnected
	signal(SIGTERM, stopRobot); // Termination request sent to the program

	Server s(3200, 'b');
	Hoek NieuweHoek;
	NieuwCommand = new robotcommand("/dev/ttyUSB0");

	for (;;) {
		s.listen();
		if (s.dataValid()) {
			t.setPositieRobot(s.getInfo().robotx, s.getInfo().roboty,
					s.getInfo().robothoek);
			t.setPositieBlikje(s.getInfo().blikx, s.getInfo().bliky);
			t.setPositieGarage(s.getInfo().garagex, s.getInfo().garagey);
#ifdef DEBUG
			std::cout << "Valid!" << std::endl;
			t.print();
#endif

			NieuweHoek.BepaalHoek(t.getPositieRobot().getX(),
					t.getPositieRobot().getY(), t.getPositieBlikje().getX(),
					t.getPositieBlikje().getY(),
					t.getPositieRobot().getAngle());
			if (NieuweHoek.getAngle() == 0) {
				NieuweHoek.BepaalAfstand(t.getPositieRobot().getX(),
						t.getPositieRobot().getY(), t.getPositieBlikje().getX(),
						t.getPositieBlikje().getY());
#ifdef DEBUG
				cout<<"Afstand = "<<NieuweHoek.getAfstand()<<endl;
#endif
				NieuweHoek.BepaalSnelheid();
				//NieuwCommand->driveForward(NieuweHoek.getSpeed());
				if (NieuweHoek.getAfstand() <= 220) {
					NieuwCommand->stop();
					NieuwCommand->gripClose();
				} else {
					if (NieuweHoek.getAfstand() >= 250) {
						//NieuwCommand->driveForward(MAXSPEED);
					} else {
						//NieuwCommand->driveForward(MINSPEED);
					}
				}
			} else {
				NieuwCommand->stop();
				NieuwCommand->turnRoundOwnAxis(NieuweHoek.getDirection(),
						NieuweHoek.getAngle());
			}
			sleep(1);

#ifdef DEBUG
			cout << "Main waarden:" << endl;
			cout << "Hoek = " << NieuweHoek.getAngle() << endl;
			cout << "Richting = " << NieuweHoek.getDirection() << endl;
			cout << "Snelheid = " << NieuweHoek.getSpeed() << endl;
#endif
		} else {
#ifdef DEBUG
			std::cout << "Niet valid!" << std::endl;
#endif
		}

	}

	return 0;
}
