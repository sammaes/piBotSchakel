#include "robotcommand.h"

using namespace std;

robotcommand::~robotcommand() {
	// TODO: Checken of delete hier moet
	//delete RobotSerialPort;
}

robotcommand::robotcommand() {
	//Open the serialport via the dedicated class
	RobotSerialPort = new serialport();

	gripOpen();	//Init Grip
	//gripstate = 0; //TODO: Gebeurt al in gripOpen()

	stop();
	//drivestate = 0; // TODO: Gebeurt al in stop();
}

// TODO: Verschil tussen deze 2 constructors ?
robotcommand::robotcommand(string port) {
	RobotSerialPort = new serialport(port);
}

// TODO: Wordt dit nog gebruikt?
int robotcommand::turnRoundOwnAxis(char direction, int angle) {
	return turnRoundOwnAxis(direction, angle, TURNSPEED);
}

int robotcommand::turnDirection(char direction,int speed)
{
		string strCmd;

		if (speed > 100)
			speed = 100; 	//clamp speed to 100 if larger

		switch (direction) {
		case 'R':
		case 'r':
			strCmd = "q " + intToString(speed) + ' ' + intToString((-1) * speed);
			break;

		case 'L':
		case 'l':
			strCmd = "q " + intToString((-1) * speed) + ' ' + intToString(speed);
			break;

		default:
			cerr << "Robotcommand:\tERROR: turnDirection Wrong Direction" << endl;
		}

		#ifdef DEBUGROBOTCOMMAND
			cout << "Robotcommand:\t turnDirection command START: ' " << strCmd << " '" << endl;
		#endif // DEBUGROBOTCOMMAND

		if (0 > RobotSerialPort->sWrite(strCmd)) {
			cerr << "Robotcommand:\tERROR: turnDirection Failed" << endl;
			return -1;
		}
		drivestate = 3;
		//sleep(ut_rotation);
		//stop();
		return 0;

}

// TODO: Wordt dit nog gebruikt?
int robotcommand::turnRoundOwnAxis(char direction, int angle, int speed) {
	string strCmd;
	unsigned int ut_rotation;

	if (speed > 100)
		speed = 100; 	//clamp speed to 100 if larger

	switch (direction) {
	case 'R':
	case 'r':
		strCmd = "q " + intToString(speed) + ' ' + intToString((-1) * speed);
		break;

	case 'L':
	case 'l':
		strCmd = "q " + intToString((-1) * speed) + ' ' + intToString(speed);
		break;

	default:
		cerr << "Robotcommand:\tERROR: turnRoundOwnAxis Wrong Direction" << endl;
	}

	ut_rotation = (abs(angle) * DEGMULT) / DEGPERSEC; //multiply by factor to get larger time to seconds

	#ifdef DEBUGROBOTCOMMAND
		cout << "Robotcommand:\t turnOwnAxis command START: ' " << strCmd << " '" << endl;
		cout << "Robotcommand:\t turnOwnAxis command TIME: " << intToString(ut_rotation) << " s" << endl;
	#endif // DEBUGROBOTCOMMAND

	if (0 > RobotSerialPort->sWrite(strCmd)) {
		cerr << "Robotcommand:\tERROR: turnOwnAxis Failed" << endl;
		return -1;
	}
	drivestate = 3;
	sleep(ut_rotation);
	stop();
	return 0;
}

int robotcommand::testStartTurn() {
	string strCmd;
	strCmd = "q 100 -100";

	#ifdef DEBUGROBOTCOMMAND
		cout << "Robotcommand:\t testStartTurn command START: ' " << strCmd << " '" << endl;
	#endif // DEBUGROBOTCOMMAND
	if (0 > RobotSerialPort->sWrite(strCmd)) {
		cerr << "Robotcommand:\tERROR: turnOwnAxis Failed" << endl;
		return -1;
	}
	drivestate = 3;
	return 0;
}

int robotcommand::driveForward(int speed) {
	string strCmd;

	if (speed > 100)
		speed = 100; //clamp speed to 100 if larger 
	strCmd = "q " + intToString(speed) + ' ' + intToString(speed);

	#ifdef DEBUGROBOTCOMMAND
		cout << "Robotcommand:\t driveForward command: ' " << strCmd << " '" << endl;
	#endif // DEBUGROBOTCOMMAND

	if (0 > RobotSerialPort->sWrite(strCmd)) {
		cerr << "Robotcommand:\tERROR: driveForwardCommand Failed" << endl;
		return -1;
	}
	drivestate = 1;
	return 0;
}

int robotcommand::driveReverse(int speed) {
	string strCmd;

	if (speed > 100)
		speed = 100; //clamp speed to 100 if larger 
	strCmd = "q " + intToString((-1) * speed) + ' ' + intToString((-1) * speed);

	#ifdef DEBUGROBOTCOMMAND
		cout << "Robotcommand:\t driveReverse command: ' " << strCmd << " '" << endl;
	#endif // DEBUGROBOTCOMMAND

	if (0 > RobotSerialPort->sWrite(strCmd)) {
		cerr << "Robotcommand:\tERROR: driveReverseCommand Failed" << endl;
		return -1;
	}
	drivestate = 2;
	return 0;
}

int robotcommand::stop() {
	string strCmd;
	strCmd = "q 0 0";

	#ifdef DEBUGROBOTCOMMAND
		cout << "Robotcommand:\t Stop command: ' " << strCmd << " '" << endl;
	#endif // DEBUGROBOTCOMMAND

	if (0 > RobotSerialPort->sWrite(strCmd)) {
		cerr << "Robotcommand:\tERROR: Stop Command Failed" << endl;
		return -1;
	}
	drivestate = 0;
	return 0;
}

int robotcommand::getDriveState() {
	return drivestate;
}

int robotcommand::gripOpen() {
	if (gripstate != 0)
	{
		string strCmd = "g 0";

		#ifdef DEBUGROBOTCOMMAND
			cout << "Robotcommand:\t Grip Open command: ' " << strCmd << " '" << endl;
		#endif // DEBUGROBOTCOMMAND

		if (0 > RobotSerialPort->sWrite(strCmd)) {
			cerr << "Robotcommand:\tERROR: Grip Open Command Failed" << endl;
			return -1;
		}
		gripstate = 0;
		return 0;
	}
	else
	{
		return 0; // TODO: mss andere waarde kiezen?
	}
}

int robotcommand::gripClose() {
	if (gripstate != 0)
	{
		string strCmd = "g 1";

		#ifdef DEBUGROBOTCOMMAND
			cout << "Robotcommand:\t Grip Close command: ' " << strCmd << " '" << endl;
		#endif // DEBUGROBOTCOMMAND

		if (0 > RobotSerialPort->sWrite(strCmd)) {
			cerr << "Robotcommand:\tERROR: Grip Close Command Failed" << endl;
			return -1;
		}
		gripstate = 1;
		return 0;
	}
	else
	{
		return 0; // TODO: mss andere waarde kiezen?
	}
}

int robotcommand::getGripState() {
	return gripstate;
}

int robotcommand::readDistance() {
	string strCmd = "u";
	char c_strRead[16];
	int distance;

	#ifdef DEBUGROBOTCOMMAND
		cout << "Robotcommand:\t Read Distance command: ' " << strCmd << " '" << endl;
	#endif // DEBUGROBOTCOMMAND

	if (0 > RobotSerialPort->sWrite(strCmd)) {
		cerr << "Robotcommand:\tERROR: Read Distance Command Failed" << endl;
		return -1;
	} else {
		//sleep(1);				//sleep if serial port needs time to answer
		RobotSerialPort->sRead(c_strRead);
		distance = atoi(c_strRead);
	}

	return distance;
}

int robotcommand::readVoltage() {
	string strCmd = "v";
	char c_strRead[16];				//Ctype string
	int voltage;

	#ifdef DEBUGROBOTCOMMAND
		cout << "Robotcommand:\t Read Distance command: ' " << strCmd << " '" << endl;
	#endif // DEBUGROBOTCOMMAND

	if (0 > RobotSerialPort->sWrite(strCmd)) {
		cerr << "Robotcommand:\tERROR: Read Distance Command Failed" << endl;
		return -1;
	} else {
		//sleep(1);				//sleep if serial port needs time to answer
		RobotSerialPort->sRead(c_strRead);
		voltage = atoi(c_strRead);
	}

	return voltage;
}

string robotcommand::intToString(int number) {
	string 			Result; 	// string which will contain the result
	ostringstream 	convert;	// stream used for the conversion
	convert << number; 			// insert the textual representation of 'Number' in the characters in the stream
	return convert.str(); 		// set 'Result' to the contents of the stream
}

int robotcommand::stringToInt(string txt) {
	int 			res;          	//number which will contain the result
	istringstream 	convert(txt); 	// stringstream used for the conversion constructed with the contents of 'Text'
									// ie: the stream will start containing the characters of 'Text'
	if (!(convert >> res))
		res = 0;					//give the value to 'Result' using the characters in the stream
	return res;
}

