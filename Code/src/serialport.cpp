#include "serialport.h"
#include <string.h>
#include <iostream>
using namespace std;

serialport::~serialport() {
	close (fd); // Close the filedescriptor
}

// constructor for port
serialport::serialport(string port) {

	struct termios term_attr;
	int err_tst;

	//open port serial port
	#ifdef DEBUGSERIALPORT
		cout << "Serialport:\t Open serial port: ";
	#endif // DEBUGSERIALPORT
	if ((this->fd = open(port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY)) == -1) {
		cerr << "\nSerialport:\tERROR: Opening port: (" << errno << ")" << endl;
		portopen = 0;
	} else {
		#ifdef DEBUGSERIALPORT
			cout << "OK" << endl;
		#endif // DEBUGSERIALPORT
	}

	//get port attributes
	#ifdef DEBUGSERIALPORT
		cout << "Serialport:\t Getting Port attributes: ";
	#endif // DEBUGSERIALPORT
	if (tcgetattr(this->fd, &term_attr)) {
		cerr << "\nSerialport:\tERROR: Getting Port Attributes" << endl;
		portopen = 0;
	} else {
		#ifdef DEBUGSERIALPORT
			cout << "OK" << endl;
		#endif // DEBUGSERIALPORT
	}

	//Next we set different port attributes to setup the serial port
	//set the baud rate
	#ifdef DEBUGSERIALPORT
		cout << "Serialport:\t Setting Baudrate RX: ";
	#endif // DEBUGSERIALPORT

	err_tst = cfsetispeed(&term_attr, B38400);
	if (err_tst == -1) {
		cerr << "\nSerialport:\tERROR: Setting RX Baudrate" << endl;
		portopen = 0;
	} else {
		//TODO maybe do getspeed
		#ifdef DEBUGSERIALPORT
			cout << "OK" << endl;
		#endif // DEBUGSERIALPORT
	}

	#ifdef DEBUGSERIALPORT
		cout << "Serialport:\t Setting Baudrate TX: ";
	#endif // DEBUGSERIALPORT

	err_tst = cfsetospeed(&term_attr, B38400);
	if (err_tst == -1) {
		cerr << "\nSerialport:\tERROR: Setting RX Baudrate" << endl;
		portopen = 0;
	} else {
		//TODO maybe do getspeed
		#ifdef DEBUGSERIALPORT
			cout << "OK" << endl;
		#endif // DEBUGSERIALPORT
	}

	//set some flags
	term_attr.c_cflag |= (CLOCAL | CREAD);
	term_attr.c_cflag &= ~PARENB;			//Clear No parity
	term_attr.c_cflag &= ~CSTOPB;			//Clear only 1 stopbit
	term_attr.c_cflag &= ~CSIZE;			//Clear size
	term_attr.c_cflag |= CS8;				//Set size to 8 bit

	//send the newly set attributes to the port to make them valid
	#ifdef DEBUGSERIALPORT
		cout << "Serialport:\t Setting New port attributes: ";
	#endif // DEBUGSERIALPORT
	if (tcsetattr(this->fd, TCSANOW, &term_attr)) {
		cerr << "\nSerialport:\tERROR: Setting New Attributes" << endl;
		portopen = 0;
	} else {
		#ifdef DEBUGSERIALPORT
			cout << "OK" << endl;
		#endif // DEBUGSERIALPORT
	}
		#ifdef DEBUGSERIALPORT
			cout << "Serialport:\t Configuring Serial Port done" << endl;
		#endif // DEBUGSERIALPORT

	// TODO staat dit hier wel goed? overschrijft de 0 van hierboven en andere plaatsen?
	portopen = 1;
}

void serialport::clearBuffer() {
	if (1 == portopen) {
		tcflush(fd, TCIFLUSH);
		sleep(2);
	} else {
		cerr << "Serialport:\tERROR: Port Not open" << endl;
	}
}

int serialport::sWrite(string command) {
	const char *temp;
	char cmd[13];
	int len;
	int byteswritten;

	//Example Command: "q -100 -100#"
	if (1 == portopen) {
		temp = command.c_str();
		strncpy(cmd, temp, 12);	//never copy more than the destination can carry
		len = strlen(cmd);
		cmd[len] = 13;			//add CR
		cmd[len + 1] = '\0';	//restore '\0' to complete string

		byteswritten = write(this->fd, cmd, strlen(cmd));
		tcdrain(fd);
		#ifdef DEBUGSERIALPORT
			cout << "Serialport:\t Write Command to serial port: ";
		#endif // DEBUGSERIALPORT
		if (byteswritten <= 0) {
			cerr << "Serialport:\tERROR: Only " << byteswritten << " bytes written" << endl;
			return -1;
		} else {
			#ifdef DEBUGSERIALPORT
				// TODO: goed dat ik command hier tussen de '' heb gezet?
				cout << "Serialport:\t OK: command '" << command << "' sent (" << byteswritten << " bytes)" << endl;
			#endif // DEBUGSERIALPORT
		}
	} else {
		cerr << "Serialport:\tERROR: Port Not open" << endl;
		return -1;
	}
	return 0;
}

int serialport::sRead(char *bufferstring) {

	int bytesread;

	if (1 == portopen) {
		fcntl(this->fd, F_SETFL, O_NONBLOCK);//don't block the reading from the port
		#ifdef DEBUGSERIALPORT
			cout << "Serialport:\t Read Values From Serial port:" << endl;
		#endif // DEBUGSERIALPORT
		bytesread = read(this->fd, bufferstring, SERIAL_BUF_LEN);

		if (bytesread < 0) {
			cerr << "Serialport:\tERROR: can't read from serial!" << endl;
			return 0;
		} else {
			#ifdef DEBUGSERIALPORT
				cout << "Serialport:\t OK: read " << bytesread << " bytes" << endl;
			#endif // DEBUGSERIALPORT
		}
	} else {
		cerr << "Serialport:\tERROR: Port Not open" << endl;
		return -1;
	}
	return bytesread;
}
