#ifdef DEBUGROBOT
		#include <iostream>
#endif // DEBUGROBOT

#include "Robot.h"

Robot::Robot(int udpPoort,string serialPoort, char groep) : Server(udpPoort, groep), robotcommand(serialPoort)
{
}

void Robot::updatePosities()
{
	if (this->dataValid())
	{
		this->setPositieRobot(this->getInfo().robotx, this->getInfo().roboty,this->getInfo().robothoek);
		this->setPositieBlikje(this->getInfo().blikx, this->getInfo().bliky);
		this->setPositieGarage(this->getInfo().garagex, this->getInfo().garagey);
	}
}

void Robot::bepaalHoekBlikje()
{
	this->BepaalHoek(this->getPositieRobot().getX(),this->getPositieRobot().getY(),this->getPositieBlikje().getX(),this->getPositieBlikje().getY(),this->getPositieRobot().getAngle());
}

void Robot::bepaalHoekGarage()
{
	this->BepaalHoek(this->getPositieRobot().getX(),this->getPositieRobot().getY(),this->getPositieGarage().getX(),this->getPositieGarage().getY(),this->getPositieRobot().getAngle());
}

void Robot::bepaalAfstandBlikje()
{
	this->BepaalAfstand(this->getPositieRobot().getX(),this->getPositieRobot().getY(),this->getPositieBlikje().getX(),this->getPositieBlikje().getY());
}

void Robot::bepaalAfstandGarage()
{
	this->BepaalAfstand(this->getPositieBlikje().getX(),this->getPositieBlikje().getY(),this->getPositieGarage().getX(),this->getPositieGarage().getY());
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
