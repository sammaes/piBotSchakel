#include "Robot.h"
#include <iostream>

Robot::Robot(int angle, int xrobot, int yrobot, int xblikje, int yblikje,
		int xgarage, int ygarage, bool grab) {
	this->setPositieRobot(xrobot, yrobot, angle);
	this->setPositieBlikje(xblikje, yblikje);
	this->setPositieGarage(xgarage, ygarage);
	this->setGrabbedItem(grab);
}

bool Robot::grabbedItem() {
	return this->grabbed;
}

void Robot::setGrabbedItem(bool val) {
	this->grabbed = val;
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

void Robot::berekenRoute() {
	double cornerDest = 0;
	double cornerRobot = this->posRobot.getAngle();

#ifdef DEBUG
	std::cout << "Berekenen van de route" << std::endl;
	std::cout << "\tPositie::    x:" << this->posRobot.getX() << " y:" << this->posRobot.getY() << " angle:" << cornerRobot << std::endl;
	//std::cout << "\tBestemming:: x:" << this->getDestination().getX() << " y:" << this->getDestination().getY() << " angle:" << cornerDest << std::endl;
#endif // DEBUG
	/* Draaien */
	if (cornerDest < cornerRobot) {
		this->turnClock(cornerRobot - cornerDest);
	} else if (cornerDest > cornerRobot) {
		this->turnAntiClock(cornerDest - cornerRobot);
	} else // Niet nodig om te draaien
	{
#ifdef DUMMY
		this->vooruit(100.0);
#else
		// beslis waar robot naartoe moet met welke snelheid
#endif // DUMMY
	}

}

/* Driving */

void Robot::vooruit(double speed) {
#ifdef DEBUG
	std::cout << "r2d2 rijdt vooruit met snelheid:" << speed << std::endl;
#endif // DEBUG
}

void Robot::achteruit(double speed) {
#ifdef DEBUG
	std::cout << "r2d2 rijdt achteruit met snelheid:" << speed << std::endl;
#endif // DEBUG
}

void Robot::turnClock(double corner) {
#ifdef DEBUG
	std::cout << "r2d2 draait clockwise over " << corner << " graden" << std::endl;
#endif // DEBUG
}

void Robot::turnAntiClock(double corner) {
#ifdef DEBUG
	std::cout << "r2d2 draait anticlockwise over " << corner << " graden" << std::endl;
#endif // DEBUG
}

void Robot::stop() {
#ifdef DEBUG
	std::cout << "r2d2 stopt" << std::endl;
#endif // DEBUG
}

void Robot::grab() {
#ifdef DEBUG
	std::cout << "r2d2 neemt blikje vast" << std::endl;
#endif // DEBUG
}

void Robot::print() {
	std::cout << "robotx:" << this->getPositieRobot().getX() << std::endl;
	std::cout << "roboty:" << this->getPositieRobot().getY() << std::endl;
	std::cout << "robothoek:" << this->getPositieRobot().getAngle()
			<< std::endl;
	std::cout << "blikjex:" << this->getPositieBlikje().getX() << std::endl;
	std::cout << "blikjey:" << this->getPositieBlikje().getY() << std::endl;
	std::cout << "garagax:" << this->getPositieGarage().getX() << std::endl;
	std::cout << "garagey:" << this->getPositieGarage().getY() << std::endl;
}
