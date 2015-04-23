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
#include <unistd.h>

#include "debug.h"
#include "Server.h"
#include "Robot.h"
#include "Hoek.h"
#include "robotcommand.h"

#define DRAAISPEEDMIN			20
#define DRAAISPEEDMAX			40
#define GROTEAFSTAND 			70
#define CIRKELTRESHOLDVANBLIK 	100
#define CIRKELTRESHOLDVANGARAGE	100
#define	CIRKELTRESHOLDVANDESTINATION	100
#define AFSTANDTUSSENROBOTBLIK	45

#define INITROBOT 				0
#define DRAAINAARBLIK 			1
#define DRAAINAARGARAGE			5
#define DRAAINAARDESTINATION	13

#define RIJNAARBLIK				2
#define	RIJNAARDESTINATION		4
#define RIJNAARGARAGE			6
#define RIJVOORUITWEGVANBLIK	9
#define RIJACHTERUITWEGVANBLIK	10

#define BIJSTURENNAARBLIK		3
#define BIJSTURENNAARGARAGE		7
#define	BIJSTURENNAARDESTINATION	8
#define IDLE					11
#define ONTWIJKEN				12

int InitRobot();
int RijVooruitWegVanBlik();
int RijAchteruitWegVanBlik(int afstand);
int DraaiNaarBlik();
int DraaiNaarDestination();
int RijNaarBlik();
int RijNaarDestination();
int BijsturenNaarBlik();
int BijsturenNaarGarage();
int BijsturenNaarDestination();
int DraaiNaarGarage();
int RijNaarGarage();
int Idle();
int Ontwijken();
void nieuwePositiesBlikje();
void nieuwePositiesGarage();
void nieuwePositiesDestination();

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
	
	Positie posBlikje;
	int fase = INITROBOT;	//init afhankelijk van positie en hoek
	t.gripOpen();
	sleep(1);
	t.gripClose();
	sleep(1);
	t.gripOpen();

	//Begin: hoek niet goed, en grote afstand
	for(;;){
			std::cout << fase << std::endl;
			switch(fase){
					case INITROBOT: 			fase = InitRobot();												//0
									break;
					case DRAAINAARBLIK : 		fase = DraaiNaarBlik();											//1
									break;
					case DRAAINAARDESTINATION :	fase = DraaiNaarDestination();									//13
									break;
					case RIJNAARBLIK :			fase = RijNaarBlik();											//2
									break;
					case BIJSTURENNAARBLIK : 	fase = BijsturenNaarBlik();										//3
									break;
					case RIJNAARDESTINATION :	fase = RijNaarDestination();									//4
									break;
					case DRAAINAARGARAGE:		fase = DraaiNaarGarage();										//5
									break;
					case RIJNAARGARAGE :		fase = RijNaarGarage();											//6
									break;
					case BIJSTURENNAARGARAGE:	fase = BijsturenNaarGarage();									//7
									break;
					case BIJSTURENNAARDESTINATION:	fase = BijsturenNaarDestination();							//8
									break;
					case RIJVOORUITWEGVANBLIK: 	fase = RijVooruitWegVanBlik();									//9
									break;
					case RIJACHTERUITWEGVANBLIK:fase = RijAchteruitWegVanBlik(CIRKELTRESHOLDVANBLIK/2);			//10
									break;
					case ONTWIJKEN :			fase = Ontwijken();												//12
									break;
					default:					fase = Idle();													//11
									break;
			}
			usleep(1000);
	}
}

int Idle(){

	t.stop();

	sleep(15);
	//stopRobot(0);
	return INITROBOT;
}

int Ontwijken(){

	nieuwePositiesDestination();

	return DRAAINAARBLIK; // of naar garage
}

int InitRobot(){
	int hoek,afstand;

	t.setInitielePosBlikjeGeset(false);
	nieuwePositiesBlikje();
	hoek = t.getAngle();
	afstand = t.getAfstand();
	std::cout << "afstand:" << afstand << " hoek:" << hoek << std::endl;
	if(t.botsing())
	{
		return DRAAINAARDESTINATION;
	}
	if(afstand <= CIRKELTRESHOLDVANBLIK && (hoek > 90 && hoek < 270 ))		//blikje staat vlak achter robot --> vooruit r
	{
		std::cout << "RIJVOORUITWEGVANBLIK" << std::endl;
		return RIJVOORUITWEGVANBLIK;
	}
	else if(afstand <= CIRKELTRESHOLDVANBLIK && !(hoek > 90 && hoek < 270))	//achteruit wegrijden van blikje
	{
		std::cout << "RIJACHTERUITWEGVANBLIK" << std::endl;
		return RIJACHTERUITWEGVANBLIK;
	}
	else
	{
		std::cout << "DRAAINAARBLIK" << std::endl;
		return DRAAINAARBLIK;
	}

	std::cout << "Geen valid data ==> blijf in INIT" << std::endl;
	return INITROBOT;
}

int DraaiNaarBlik(){
	if (t.blikjeVerplaatst())
	{
		std::cout << "Blikje verplaatst!" << std::endl;
		return INITROBOT;
	}

	nieuwePositiesBlikje();

	t.turnDirection(t.getDirection(),DRAAISPEEDMAX);
	while((t.getAngle() != 0) && (!t.blikjeVerplaatst())){
		t.listen();
		if(t.dataEigenValid()){
			t.updatePosities();
			t.bepaalHoekBlikje();
		}
	}
	t.stop();
	
	std::cout << "Robot is gedraaid naar blik" << std::endl;

	if (t.blikjeVerplaatst())
	{
		std::cout << "Blikje verplaatst!" << std::endl;
		return INITROBOT;
	}
	else if (t.getAfstand() > CIRKELTRESHOLDVANBLIK)	// Buiten cirkel van blikje
	{
		return RIJNAARBLIK;
	}
	else		// Binnen cirkel van blikje
	{
		return BIJSTURENNAARBLIK;
	}

}

int DraaiNaarDestination() {
	nieuwePositiesDestination();

	t.turnDirection(t.getDirection(),DRAAISPEEDMAX);
	while(t.getAngle() != 0){
		t.listen();
		if(t.dataEigenValid()){
			t.updatePosities();
			t.bepaalHoekDestination();
		}
	}
	t.stop();
	t.bepaalAfstandDestination();

	std::cout << "Robot is gedraaid naar destination" << std::endl;
	stopRobot(0);
	return 0;
	//return RIJNAARDESTINATION;
	/*
	if (t.getAfstand() > CIRKELTRESHOLDVANDESTINATION)	// Buiten cirkel van garage
	{
		return RIJNAARDESTINATION;
	}
	else		// Binnen cirkel van garage
	{
		return BIJSTURENNAARDESTINATION;
	}
	*/
}

int DraaiNaarGarage() {
	nieuwePositiesGarage();

	t.turnDirection(t.getDirection(),DRAAISPEEDMAX);
	while(t.getAngle() != 0){
		t.listen();
		if(t.dataEigenValid()){
			t.updatePosities();
			t.bepaalHoekGarage();
		}
	}
	t.stop();
	t.bepaalAfstandGarage();

	std::cout << "Robot is gedraaid naar garage" << std::endl;

	if (t.getAfstand() > CIRKELTRESHOLDVANGARAGE)	// Buiten cirkel van garage
	{
		return RIJNAARGARAGE;
	}
	else		// Binnen cirkel van garage
	{
		return BIJSTURENNAARGARAGE;
	}
}

int RijVooruitWegVanBlik(){
	nieuwePositiesBlikje();

	t.driveForward(MINSPEED);
	std::cout << "Afstand voor:" << t.getAfstand() << std::endl;
	while(t.getAfstand() <= CIRKELTRESHOLDVANBLIK){

		t.listen();
		if(t.dataEigenValid()){
			t.updatePosities();
			t.bepaalAfstandBlikje();
			std::cout << "Afstand in while:" << t.getAfstand() << std::endl;
		}
	}
	t.stop();
	std::cout << "Robot is weggereden van blikje" << std::endl;
	return DRAAINAARBLIK;
}
int RijAchteruitWegVanBlik(int afstand){
	nieuwePositiesBlikje();

	t.driveReverse(MINSPEED);
	while(t.getAfstand() <= afstand){
		t.listen();
		if(t.dataEigenValid()){
			t.updatePosities();
			t.bepaalAfstandBlikje();
		}
	}
	t.stop();
	std::cout << "Robot is weggereden van blikje" << std::endl;

	if (t.getAfstand() > CIRKELTRESHOLDVANBLIK)	// Buiten cirkel van blikje
	{
		return RIJNAARBLIK;
	}
	else		// Binnen cirkel van blikje
	{
		return BIJSTURENNAARBLIK;
	}
}

int RijNaarBlik() {
	if (t.blikjeVerplaatst())
	{
		std::cout << "Blikje verplaatst!" << std::endl;
		return INITROBOT;
	}

	nieuwePositiesBlikje();

	if (t.getAfstand() >= CIRKELTRESHOLDVANBLIK)
	t.driveForward(MAXSPEED);
	std::cout << "RNB: Afstand voor:" << t.getAfstand() << std::endl;

	while((t.getAfstand() >= CIRKELTRESHOLDVANBLIK) && (!t.blikjeVerplaatst())){
		t.listen();
		if(t.dataEigenValid()){
			std::cout << "RNB: Afstand in while:" << t.getAfstand() << std::endl;
			t.updatePosities();
			t.bepaalAfstandBlikje();
		}
	}

	while(t.getDriveState() != 0)
		t.stop();


	if (t.blikjeVerplaatst())
	{
		std::cout << "Blikje verplaatst!" << std::endl;
		return INITROBOT;
	}
	else
	{
		std::cout << "RNB: Robot is aangekomen bij blikje" << std::endl;
		return BIJSTURENNAARBLIK;
	}
}

int RijNaarGarage() {
	nieuwePositiesGarage();

	if (t.getAfstand() >= CIRKELTRESHOLDVANGARAGE)
	t.driveForward(MAXSPEED);
	std::cout << "RNG: Afstand voor:" << t.getAfstand() << std::endl;

	while(t.getAfstand() >= CIRKELTRESHOLDVANGARAGE){
		t.listen();
		if(t.dataEigenValid()){
			std::cout << "RNG: Afstand in while:" << t.getAfstand() << std::endl;
			t.updatePosities();
			t.bepaalAfstandGarage();
		}
	}

	while(t.getDriveState() != 0)
		t.stop();

	std::cout << "RNG: Robot is aangekomen bij blikje" << std::endl;
	return BIJSTURENNAARGARAGE;
}

int RijNaarDestination() {
	nieuwePositiesDestination();

	if (t.getAfstand() >= CIRKELTRESHOLDVANDESTINATION)
	t.driveForward(MAXSPEED);
	std::cout << "RND: Afstand voor:" << t.getAfstand() << std::endl;

	while(t.getAfstand() >= CIRKELTRESHOLDVANDESTINATION){
		t.listen();
		if(t.dataEigenValid()){
			std::cout << "RND: Afstand in while:" << t.getAfstand() << std::endl;
			t.updatePosities();
			t.bepaalAfstandDestination();
		}
	}

	t.stop();

	std::cout << "RND: Robot is aangekomen bij destination" << std::endl;
	return DRAAINAARBLIK;
}

int BijsturenNaarBlik() {
	nieuwePositiesBlikje();

	do {
		t.listen();
		if(t.dataEigenValid()){
			t.updatePosities();
			t.bepaalHoekBlikje();
		}
	} while(!t.dataEigenValid());


	t.turnDirection(t.getDirection(),DRAAISPEEDMIN);
	while(t.getAngle() != 0){
		t.listen();
		if(t.dataEigenValid()){
			t.updatePosities();
			t.bepaalHoekBlikje();
		}
	}
	t.stop();

	t.driveForward(MINSPEED);
	std::cout << "Afstand voor:" << t.getAfstand() << std::endl;
	while(t.getAfstand() >= AFSTANDTUSSENROBOTBLIK){

		t.listen();
		if(t.dataEigenValid()){
			t.updatePosities();
			t.bepaalAfstandBlikje();
			std::cout << "Afstand in while:" << t.getAfstand() << std::endl;
		}
	}
	t.stop();

	t.gripClose();

	std::cout << "Robot is bijgestuurd en grijper is dicht" << std::endl;

	return DRAAINAARGARAGE;
}

int BijsturenNaarGarage() {
	nieuwePositiesGarage();

	do {
		t.listen();
		if(t.dataEigenValid()){
			t.updatePosities();
			t.bepaalHoekGarage();
		}
	} while(!t.dataEigenValid());


	t.turnDirection(t.getDirection(),DRAAISPEEDMIN);
	while(t.getAngle() != 0){
		t.listen();
		if(t.dataEigenValid()){
			t.updatePosities();
			t.bepaalHoekGarage();
		}
	}
	t.stop();

	t.driveForward(MINSPEED);
	std::cout << "Afstand voor:" << t.getAfstand() << std::endl;
	while(t.getAfstand() >= 25){

		t.listen();
		if(t.dataEigenValid()){
			t.updatePosities();
			t.bepaalAfstandGarage();
			std::cout << "Afstand in while:" << t.getAfstand() << std::endl;
		}
	}

	t.stop();

	t.gripOpen();

	std::cout << "nog enkel achteruit rijden aub" << std::endl;
	RijAchteruitWegVanBlik(CIRKELTRESHOLDVANGARAGE);
	std::cout << "Ik ben braaf achteruit gereden" << std::endl;

	std::cout << "Robot is bijgestuurd en grijper is open" << std::endl;

	return IDLE;
}
int BijsturenNaarDestination() {
	nieuwePositiesDestination();

	do {
		t.listen();
		if(t.dataEigenValid()){
			t.updatePosities();
			t.bepaalHoekDestination();
		}
	} while(!t.dataEigenValid());


	t.turnDirection(t.getDirection(),DRAAISPEEDMIN);
	while(t.getAngle() != 0){
		t.listen();
		if(t.dataEigenValid()){
			t.updatePosities();
			t.bepaalHoekDestination();
		}
	}
	t.stop();

	t.driveForward(MINSPEED);
	std::cout << "Afstand voor:" << t.getAfstand() << std::endl;
	while(t.getAfstand() >= 25){

		t.listen();
		if(t.dataEigenValid()){
			t.updatePosities();
			t.bepaalAfstandDestination();
			std::cout << "Afstand in while:" << t.getAfstand() << std::endl;
		}
	}

	t.stop();

	t.gripOpen();

	std::cout << "nog enkel achteruit rijden aub" << std::endl;
	RijAchteruitWegVanBlik(CIRKELTRESHOLDVANGARAGE);
	std::cout << "Ik ben braaf achteruit gereden" << std::endl;

	std::cout << "Robot is bijgestuurd en grijper is open" << std::endl;

	return IDLE;
}

void nieuwePositiesBlikje()
{
	do {
		t.listen();
	} while(!t.dataEigenValid());
	t.updatePosities();
	t.bepaalAfstandBlikje();
	t.bepaalHoekBlikje();
}

void nieuwePositiesGarage()
{
	do {
		t.listen();
	} while(!t.dataEigenValid());
	t.updatePosities();
	t.bepaalAfstandGarage();
	t.bepaalHoekGarage();
}

void nieuwePositiesDestination()
{
	do {
		t.listen();
	} while(!t.dataEigenValid());
	t.updatePosities();
	t.bepaalAfstandDestination();
	t.bepaalHoekDestination();
}
