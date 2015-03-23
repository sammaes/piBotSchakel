#include "robotcommand.h"
//#include <string>
//#include <iostream>

using namespace std;

// ---------------------------------------------------------------------------
// Destructor
robotcommand::~robotcommand()
{

}

// ---------------------------------------------------------------------------
// constructor
robotcommand::robotcommand()
{
	//Open the serialport via the dedicated class
	RobotSerialPort = new serialport();

	gripOpen();	//Init Grip
	gripstate = 0;	

	stop();	
	drivestate = 0;
}

robotcommand::robotcommand(string port)
{
	RobotSerialPort = new serialport(port);
}

int robotcommand::turnRoundOwnAxis(char direction, int angle)
{
	return turnRoundOwnAxis(direction, angle, TURNSPEED);
}

int robotcommand::turnRoundOwnAxis(char direction, int angle, int speed)
{
	string strCmd;
	unsigned int ut_rotation;

	if(speed > 100) speed = 100; 	//clamp speed to 100 if larger

	switch (direction)
	{
		case 'R':
		case 'r':	strCmd = "q " + intToString(speed) + ' ' + intToString((-1)*speed);
				break;
				
		case 'L':
		case 'l':	strCmd = "q " + intToString((-1)*speed) + ' ' + intToString(speed);
				break;

		default :
				cout << "turnOwnAxis Wrong Direction" <<endl;
	}
 	
	
	ut_rotation = (abs(angle)*DEGMULT)/DEGPERSEC; //multiply by factor to get larger time to seconds
	

	cout << "turnOwnAxis command START: ' " << strCmd << " '" << endl;
	cout << "turnOwnAxis command TIME: " << intToString(ut_rotation) << " s" << endl;
	if (0 > RobotSerialPort->sWrite(strCmd))
	{
		cout << "ERROR: turnOwnAxis Failed\n";
		return -1;
	}
	drivestate = 3;
	sleep(ut_rotation);
	stop();
	return 0;
}

int robotcommand::testStartTurn()
{
	string strCmd;
	strCmd = "q 100 -100";
	
	cout << "turnOwnAxis command START: ' " << strCmd << " '" << endl;
	if (0 > RobotSerialPort->sWrite(strCmd))
	{
		cout << "ERROR: turnOwnAxis Failed\n";
		return -1;
	}
	drivestate = 3;
	return 0;
}


int robotcommand::driveForward(int speed)
{
	string strCmd;
	
	if(speed > 100) speed = 100; //clamp speed to 100 if larger 
	strCmd = "q " + intToString(speed) + ' ' + intToString(speed);

	cout << "driveForward command: ' " << strCmd << " '" << endl;
	if (0 > RobotSerialPort->sWrite(strCmd))
	{
		cout << "ERROR: driveForwardCommand Failed\n";
		return -1;
	}
	drivestate = 1;
	return 0;
}

int robotcommand::driveReverse(int speed)
{
	string strCmd;

	if(speed > 100) speed = 100; //clamp speed to 100 if larger 
	strCmd = "q " + intToString((-1)*speed) + ' ' + intToString((-1)*speed);

	cout << "driveReverse command: ' " << strCmd << " '" << endl;
	if (0 > RobotSerialPort->sWrite(strCmd))
	{
		cout << "ERROR: driveReverseCommand Failed\n";
		return -1;
	}
	drivestate = 2;
	return 0;
}

int robotcommand::stop()
{
	string strCmd;
	strCmd = "q 0 0";

	cout << "Stop command: ' " << strCmd << " '" << endl;
	if (0 > RobotSerialPort->sWrite(strCmd))
	{
		cout << "ERROR: Stop Command Failed\n";
		return -1;
	}
	drivestate = 0;
	return 0;
}

int robotcommand::getDriveState()
{
	return drivestate;
}

int robotcommand::gripOpen()
{
	string strCmd = "g 0";

	cout << "Grip Open command:" << endl;
	if (0 > RobotSerialPort->sWrite(strCmd))
	{
		cout << "ERROR: Grip Open Command Failed\n";
		return -1;
	}
	gripstate = 0;
	return 0;
}

int robotcommand::gripClose()
{
	string strCmd = "g 1";

	cout << "Grip Close command:" << endl;
	if (0 > RobotSerialPort->sWrite(strCmd))
	{
		cout << "ERROR: Grip Close Command Failed\n";
		return -1;
	}
	gripstate = 1;
	return 0;
}

int robotcommand::getGripState()
{
	return gripstate;
}

int robotcommand::readDistance()
{
	string strCmd = "u";
	char c_strRead[16];
	int distance;

	cout << "Read Distance command:" << endl;
	if (0 > RobotSerialPort->sWrite(strCmd))
	{
		cout << "ERROR: Read Distance Command Failed\n";
		return -1;
	}
	else
	{
		//sleep(1);				//sleep if serial port needs time to answer
		RobotSerialPort->sRead(c_strRead);
		distance = atoi(c_strRead);
	}

	return distance;
}

int robotcommand::readVoltage()
{
	string strCmd = "v";
	char c_strRead[16];				//Ctype string
	int voltage;

	cout << "Read Distance command:" << endl;
	if (0 > RobotSerialPort->sWrite(strCmd))
	{
		cout << "ERROR: Read Distance Command Failed\n";
		return -1;
	}
	else
	{
		//sleep(1);				//sleep if serial port needs time to answer
		RobotSerialPort->sRead(c_strRead);
		voltage = atoi(c_strRead);
	}

	return voltage;
}

string robotcommand::intToString(int number)
{
	string Result;          		// string which will contain the result
	ostringstream convert;   		// stream used for the conversion
	convert << number;      		// insert the textual representation of 'Number' in the characters in the stream
	return convert.str(); 			// set 'Result' to the contents of the stream
}

int robotcommand::stringToInt(string txt)
{
	int res;          			//number which will contain the result
	istringstream convert(txt); 		// stringstream used for the conversion constructed with the contents of 'Text' 
                             			// ie: the stream will start containing the characters of 'Text'
	if (!(convert >> res)) res = 0;		//give the value to 'Result' using the characters in the stream
	return res;	         
}


