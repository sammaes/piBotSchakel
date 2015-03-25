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

#include "debug.h"
#include "Server.h"
#include "Robot.h"
#include "Hoek.h"
#include "robotcommand.h"
#define SPEED 10
#define GROTEAFSTAND 70
Robot t(3200,"/dev/ttyUSB0",'b');

void stopRobot(int signum) {
	#ifdef DEBUGMAIN
		std::cout << "\nSignaal (" << signum << ") ontvangen" << std::endl;
	#endif // DEBUGMAIN
	sleep(2);
	t.stop();

	exit(signum);
}

int main() {

	signal(SIGQUIT, stopRobot);
	signal(SIGINT, stopRobot);  // CTRL+C ingedrukt
	signal(SIGHUP, stopRobot);  // Terminal disconnected
	signal(SIGTERM, stopRobot); // Termination request sent to the program

	bool missionPhase = true; 	// True: naar blikje rijden, False: naar garage rijden
	int hoek;
	int afstand;
	unsigned long int i=0;

	t.gripOpen();
	sleep(1);
	t.gripClose();
	sleep(1);
	t.gripOpen();
	sleep(1);

	for (;;) {
		t.listen();
		if (t.dataValid()) {
			t.updatePosities();

			std::cout << "Main:\t" << (missionPhase ? " Naar blikje rijden" : " Naar garage rijden") << std::endl;

			cout << i++ << "start berekening" << std::endl;
			if (missionPhase)
			{
				t.bepaalHoekBlikje();
				t.bepaalAfstandBlikje();
				hoek = t.getAngle();		//TODO: Mogelijk om afstand en hoek te laten returnen door de bepaalfuncties?
				afstand = t.getAfstand();
			}
			else
			{
				t.bepaalHoekGarage();
				t.bepaalAfstandGarage();
				hoek = t.getAngle();
				afstand = t.getAfstand();
			}
			std::cout << "stop berekening" << std::endl;

			#ifdef DEBUGMAIN
				std::cout << "Main:\t Main waarden:" << std::endl;
				std::cout << "     \t Hoek = " << hoek << std::endl;
				std::cout << "     \t Afstand = " << afstand <<endl;
			#endif // DEBUGMAIN

			if (hoek == 0) {

				if ( (afstand <= 40) && (missionPhase) ) { // Blikje zit in de grijper -> grijp!
					t.stop();
					t.gripClose(); // Blikje vast
					#ifdef DEBUGMAIN
						std::cout << "Main:\t Blikje vastgegrepen" << std::endl;
					#endif // DEBUGMAIN
					sleep(1); 				   // Even rusten
					missionPhase = !missionPhase;
				}
				else if ( (afstand <= 10) && (!missionPhase) ) { // Bij garage -> blikje afzetten
					t.stop();
					t.gripOpen(); // Blikje open
					#ifdef DEBUGMAIN
						std::cout << "Main:\t Blikje afgeleverd" << std::endl;
					#endif // DEBUGMAIN
					t.driveReverse(40);
					sleep(3);
					t.stop();
					missionPhase = !missionPhase;
					cout << "Druk op enter om terug naar blikje te rijden:" << endl;
					cin.ignore();

				}
				else { // We zijn er nog niet.
					if (afstand >= GROTEAFSTAND) {
						t.driveForward(MAXSPEED);
						#ifdef DEBUGMAIN
							std::cout << "Main:\t Ver weg van blikje met 0 hoek -> MAXSPEED vooruit" << std::endl;
						#endif // DEBUGMAIN
					} else {
						t.driveForward(MINSPEED);
						#ifdef DEBUGMAIN
							std::cout << "Main:\t Vlakbij blikje met 0 hoek -> MINSPEED vooruit" << std::endl;
						#endif // DEBUGMAIN
					}
				}
			} else { // Hoek != 0 -> draaien
				if ( afstand < GROTEAFSTAND) // We zijn er bijna maar gaan blikje omver rijden
				{
					t.driveReverse(MINSPEED);
					#ifdef DEBUGMAIN
						std::cout << "Main:\t Vlakbij blikje met hoek != 0 -> MINSPEED achteruit" << std::endl;
					#endif // DEBUGMAIN
				}
				else // We zijn er nog niet bijna
				{
					if (hoek > 10)
					{
						t.turnDirection(t.getDirection(),40);
						#ifdef DEBUGMAIN
							std::cout << "Main:\t Ver weg van blikje met GROTE hoek -> snel draaien" << std::endl;
						#endif // DEBUGMAIN
					}
					else
					{
						#ifdef DEBUGMAIN
							std::cout << "Main:\t Ver weg van blikje met KLEINE hoek -> traag draaien" << std::endl;
						#endif // DEBUGMAIN
						t.turnDirection(t.getDirection(),SPEED);
					}
				}
			}
		}
	}

	return 0;
}
