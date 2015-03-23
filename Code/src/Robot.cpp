#ifdef DEBUGROBOT
		#include <iostream>
#endif // DEBUGROBOT

#include "Robot.h"

Robot::Robot()
{

}

Positie Robot::getPositieRobot() {
	return this->posRobot;
}

void Robot::setPositieRobot(Positie val) {
	this->posRobot = val;
}

void Robot::setPositieRobot(int x, int y, int angle) {
	this->posRobot.setAngle(angle);
	this->posRobot.setX(x);
	this->posRobot.setY(y);
}

Positie Robot::getPositieBlikje() {
	return this->posBlikje;
}

void Robot::setPositieBlikje(Positie val) {
	this->posBlikje = val;
}

void Robot::setPositieBlikje(int x, int y) {
	this->posBlikje.setX(x);
	this->posBlikje.setY(y);
}

Positie Robot::getPositieGarage() {
	return this->posGarage;
}

void Robot::setPositieGarage(Positie val) {
	this->posGarage = val;
}

void Robot::setPositieGarage(int x, int y) {
	this->posGarage.setX(x);
	this->posGarage.setY(y);
}

/* Driving */

void Robot::vooruit(double speed) {
	#ifdef DEBUGROBOT
		std::cout << "Robot:\t Robot rijdt vooruit met snelheid:" << speed << std::endl;
	#endif // DEBUGROBOT
}

void Robot::achteruit(double speed) {
	#ifdef DEBUGROBOT
		std::cout << "Robot:\t Robot rijdt achteruit met snelheid:" << speed << std::endl;
	#endif // DEBUGROBOT
}

void Robot::turnClock(double corner) {
	#ifdef DEBUGROBOT
		std::cout << "Robot:\t Robot draait clockwise over " << corner << " graden" << std::endl;
	#endif // DEBUGROBOT
}

void Robot::turnAntiClock(double corner) {
	#ifdef DEBUGROBOT
		std::cout << "Robot:\t Robot draait anticlockwise over " << corner << " graden" << std::endl;
	#endif // DEBUGROBOT
}

void Robot::stop() {
	#ifdef DEBUGROBOT
		std::cout << "Robot:\t Robot stopt" << std::endl;
	#endif // DEBUGROBOT
}

void Robot::grab() {
	#ifdef DEBUGROBOT
		std::cout << "Robot:\t Robot neemt blikje vast" << std::endl;
	#endif // DEBUGROBOT
}

void Robot::print() {
	#ifdef DEBUGROBOT
		std::cout << "robotx:" << this->getPositieRobot().getX() << std::endl;
		std::cout << "roboty:" << this->getPositieRobot().getY() << std::endl;
		std::cout << "robothoek:" << this->getPositieRobot().getAngle()	<< std::endl;
		std::cout << "blikjex:" << this->getPositieBlikje().getX() << std::endl;
		std::cout << "blikjey:" << this->getPositieBlikje().getY() << std::endl;
		std::cout << "garagax:" << this->getPositieGarage().getX() << std::endl;
		std::cout << "garagey:" << this->getPositieGarage().getY() << std::endl;
	#endif // DEBUGROBOT
}
