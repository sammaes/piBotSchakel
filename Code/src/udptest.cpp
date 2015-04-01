//============================================================================
// Name : UDP.cpp
// Author : Sam
// Version :
// Copyright : copyright
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




enum Phases{
		InitRobot,
		DraaiNaarBlik,
		RijNaarBlik,
		BijsturenNaarBlik,
		GrijpBlik,
		DraaiNaarGarage,
		RijNaarGarage,
		BijsturenNaarGarage,
		BlikjeLoslaten,
		RijVooruitWegVanBlik,
		RijAchteruitWegVanBlik
};

Phases InitRobot();
Phases RijVooruitWegVanBlik();
Phases RijAchteruitWegVanBlik();
void functie();

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
	signal(SIGINT, stopRobot); // CTRL+C ingedrukt
	signal(SIGHUP, stopRobot); // Terminal disconnected
	signal(SIGTERM, stopRobot); // Termination request sent to the program
	//bool missionPhase = true; // True: naar blikje rijden, False: naar garage rijden
	int hoek;
	int afstand;
	unsigned long int i=0;

	
	Phases fase = initRobot;	//init afhankelijk van positie en hoek
	t.gripOpen();
	sleep(1);
	t.gripClose();
	sleep(1);
	t.gripOpen();


	//Begin: hoek niet goed, en grote afstand
	for(;;){
		
		
			switch(fase){
					case 'InitRobot': 		fase = InitRobot();	//0
									break;
					case 'DraaiNaarBlik' : 		fase = DraaiNaarBlik();	//1
									break;
					case 'RijNaarBlik' :		functie();		//2
									break;
					case 'BijsturenNaarBlik' : 	functie();		//3
									break;
					case 'GrijpBlik' :		functie();		//4
									break;
					case 'DraaiNaarGarage' :	functie();		//5
									break;
					case 'RijNaarGarage' :		functie();		//6
									break;
					case 'BijsturenNaarGarage' :	functie();		//7
									break;
					case 'BlikjeLoslaten' :		functie();		//8
									break;
					case 'RijVooruitWegVanBlik' : 	fase = RijVooruitWegVanBlik();		//9
									break;
					case 'RijAchteruitWegVanBlik' :	fase = RijAchteruitWegVanBlik();		//10
									break;
			}
		
			

	}
}
Phases InitRobot(){
	int hoek,afstand;
	t.listen();
	if(t.dataValid()){
		t.bepaalHoekBlikje();
		t.bepaalAfstandBlikje();
		hoek = t.getAngle(); 
		afstand = t.getAfstand();
		if(afstand <= 40 && (hoek > 90 && hoek < 270 ))		//blikje staat vlak achter robot --> vooruit r
			return Phases.RijVooruitWegVanBlik;
		else if(afstand <= 40 && !(hoek > 90 && hoek < 270))	//achteruit wegrijden van blikje
			return Phases.RijAchteruitWegVanBlik;
		else
			return Phases.DraaiNaarBlik;
	}

}
Phases DraaiNaarBlik(){
	t.turnDirection(t.getDirection(),40);
	while(t.getHoek() != 0){
		t.listen();
		if(t.dataValid()){
			t.bepaalHoekBlikje();
		}
	}
	t.stop();
	
	std::cout << "Robot is gedraaid" << std::endl;
	return Phases.RijNaarBlik;
}

Phases RijVooruitWegVanBlik(){
	t.driveForward(MINSPEED);
	while(t.getAfstand() <= 80){
		t.listen();
		if(t.dataValid()){
			t.bepaalAfstandBlikje();
		}
	}
	t.stop();
	
	std::cout << "Robot is weggereden van blikje" << std::endl;
	return Phases.DraaiNaarBlik;
}
Phases RijAchteruitWegVanBlik(){
	t.driveReverse(MINSPEED);
	while(t.getAfstand() <= 80){
		t.listen();
		if(t.dataValid()){
			t.bepaalAfstandBlikje();
		}
	}
	t.stop();
	
	std::cout << "Robot is weggereden van blikje" << std::endl;
	return Phases.DraaiNaarBlik;
}
void functie(){
	stopRobot();	
}
