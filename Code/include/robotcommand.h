
#ifndef ROBOTCOMMAND_H_
#define ROBOTCOMMAND_H_

//System includes
#include 		<iostream>
#include 		<string>
#include 		<sstream>		//stringstream for string to int and viceversa
#include 		<cmath>
#include 		<stdlib.h>		//Use this to process Ctype string atoi()

//User Includes
#include 		"serialport.h"

#define 		TURNSPEED	100
#define 		DEGMULT		100
#define 		DEGPERSEC 	4500

using namespace std;

class robotcommand {

private:
	//Vars
	serialport 	*RobotSerialPort;
	int 		gripstate;			//0 - grip open, 1 - grip closed
	int 		drivestate;			//0 - nop, 1 forwarddrive, 2 reverse, 3 turnroundownaxis

	//Funcs
	string 		intToString(int number);
	int 		stringToInt(string txt);
	int 		turnRoundOwnAxis(char direction, int angle, int speed);
	
public:
				~robotcommand();
				robotcommand();
				robotcommand(string port);
	int 		turnRoundOwnAxis(char direction, int angle);
	int 		turnDirection(char direction, int speed);
	int 		driveForward(int speed);
	int 		driveReverse(int speed);
	int 		stop();
	int 		getDriveState();
	int 		gripOpen();
	int 		gripClose();
	int 		getGripState();
	int 		readDistance();
	int 		readVoltage();

	//Funcs for finetuing of turntime
	int 		testStartTurn();

};

#endif
