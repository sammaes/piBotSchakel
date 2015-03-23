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
#define SPEED 10
#define GROTEAFSTAND 70
Robot t;

robotcommand* NieuwCommand;

void stopRobot(int signum) {
	#ifdef DEBUG
		std::cout << "\nSignaal (" << signum << ") ontvangen" << std::endl;
	#endif
	sleep(1);
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
	int missionPhase = 1;

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

			if (missionPhase == 1)
			{
			NieuweHoek.BepaalHoek(t.getPositieRobot().getX(),
					t.getPositieRobot().getY(), t.getPositieBlikje().getX(),
					t.getPositieBlikje().getY(),
					t.getPositieRobot().getAngle());
			NieuweHoek.BepaalAfstand(t.getPositieRobot().getX(),
									t.getPositieRobot().getY(), t.getPositieBlikje().getX(),
									t.getPositieBlikje().getY());
			}
			else
			{
				NieuweHoek.BepaalHoek(t.getPositieRobot().getX(),
									t.getPositieRobot().getY(), t.getPositieGarage().getX(),
									t.getPositieGarage().getY(),
									t.getPositieRobot().getAngle());
				NieuweHoek.BepaalAfstand(t.getPositieRobot().getX(),t.getPositieRobot().getY(), t.getPositieGarage().getX(),t.getPositieGarage().getY());
			}

			if (NieuweHoek.getAngle() == 0) {
				#ifdef DEBUG
					cout<<"Afstand = "<<NieuweHoek.getAfstand()<<endl;
				#endif
				//NieuweHoek.BepaalSnelheid();
				//NieuwCommand->driveForward(NieuweHoek.getSpeed());
				if ( (NieuweHoek.getAfstand() <= 40) && (missionPhase==1) ) { // BLikje zit in de grijper -> grijp!
					NieuwCommand->stop();
					if(1 != NieuwCommand->getGripState())
					{
						NieuwCommand->gripClose(); // Blikje vast
						sleep(1); 				   // Even rusten
						missionPhase *= -1;

					}
				}
				else if ( (NieuweHoek.getAfstand() <= 40) && (missionPhase==-1) ) { // Bij garage -> blikje afzetten
					NieuwCommand->stop();
					if(0 != NieuwCommand->getGripState())
					{
						NieuwCommand->gripOpen(); // Blikje open
						NieuwCommand->driveReverse(40);
						sleep(1); 				   // Even rusten
						missionPhase *= -1;
					}
				}
				else { // We zijn er nog niet.
					if (NieuweHoek.getAfstand() >= GROTEAFSTAND) {
						NieuwCommand->driveForward(MAXSPEED);
					} else {
						NieuwCommand->driveForward(MINSPEED);
					}
				}
			} else { // Hoek != 0 -> draaien
				if ( NieuweHoek.getAfstand() < GROTEAFSTAND)
				{
					NieuwCommand->driveReverse(40);
				}
				else
				{
					if ((NieuweHoek.getAngle() > 10) && (NieuweHoek.getAfstand() >= GROTEAFSTAND))
						NieuwCommand->turnDirection(NieuweHoek.getDirection(),40);
					else
						NieuwCommand->turnDirection(NieuweHoek.getDirection(),SPEED);
				}
			}

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
