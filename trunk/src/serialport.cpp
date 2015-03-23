#include "serialport.h"
#include <string.h>
#include <iostream>
using namespace std;

// ---------------------------------------------------------------------------
// Destructor for port
serialport::~serialport() {
	// Close the filedescriptor
	close (fd);
}

// ---------------------------------------------------------------------------
// constructor for port
serialport::serialport() {
	serialport (PORT);
}

// constructor for port
serialport::serialport(string port) {

	struct termios term_attr;
	int err_tst;

	//open port serial port
#ifdef DEBUG
	printf("Open serial port: ");
#endif
	if ((this->fd = open(port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY)) == -1) {
#ifdef DEBUG
		printf("\nERROR: Opeing port: (%d) \n", errno);
#endif
		portopen = 0;
	} else {
#ifdef DEBUG
		printf("OK\n");
#endif
	}

	//get port attributes
#ifdef DEBUG
	printf("Getting Port attributes: ");
#endif
	if (tcgetattr(this->fd, &term_attr)) {
#ifdef DEBUG
		printf("\nERROR: Getting Port Attributes\n");
#endif
		portopen = 0;
	} else {
#ifdef DEBUG
		printf("OK\n");
#endif
	}

	//Next we set different port attributes to setup teh serial port
	//set the baud rate
#ifdef DEBUG
	printf("Setting Baudrate RX: ");
#endif
	err_tst = cfsetispeed(&term_attr, B38400);
	if (err_tst == -1) {
#ifdef DEBUG
		printf("\nERROR: Setting RX Baudrate\n");
#endif
		portopen = 0;
	} else {
		//maybe do getspeed
#ifdef DEBUG
		printf("OK\n");
#endif
	}

#ifdef DEBUG
	printf("Setting Baudrate TX: ");
#endif
	err_tst = cfsetospeed(&term_attr, B38400);
	if (err_tst == -1) {
#ifdef DEBUG
		printf("\nERROR: Setting RX Baudrate\n");
#endif
		portopen = 0;
	} else {
		//maybe do getspeed
#ifdef DEBUG
		printf("OK\n");
#endif
	}

	//set some flags
	term_attr.c_cflag |= (CLOCAL | CREAD);
	term_attr.c_cflag &= ~PARENB;			//Clear No parity
	term_attr.c_cflag &= ~CSTOPB;			//Clear only 1 stopbit
	term_attr.c_cflag &= ~CSIZE;			//Clear size
	term_attr.c_cflag |= CS8;			//Set size to 8 bit

	//send the newly set attributes to the port to make them valid
#ifdef DEBUG
	printf("Setting New port attributes: ");
#endif
	if (tcsetattr(this->fd, TCSANOW, &term_attr)) {
#ifdef DEBUG
		printf("\nERROR: Setting New Attributes\n");
#endif
		portopen = 0;
	} else {
#ifdef DEBUG
		printf("OK\n");
#endif
	}
#ifdef DEBUG	
	printf("\nConfiguring Serial Port done\n");
#endif

	portopen = 1;
}

void serialport::clearBuffer() {
	if (1 == portopen) {
		tcflush(fd, TCIFLUSH);
		sleep(2);
	} else {
#ifdef DEBUG
		printf("\nERROR: Port Not open\n");
#endif
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
		cmd[len] = 13;		//add CR
		cmd[len + 1] = '\0';	//restore '\0' to complete string

		byteswritten = write(this->fd, cmd, strlen(cmd));
#ifdef DEBUG
		printf("Write Command to serial port: ");
#endif
		if (byteswritten <= 0) {
#ifdef DEBUG
			printf("ERROR: Only %d bytes written\n", byteswritten);
#endif
			return -1;
		} else {
#ifdef DEBUG
			printf("OK: command '' sent (%d bytes) \n", byteswritten);
#endif
		}
	} else {
#ifdef DEBUG
		printf("\nERROR: Port Not open\n");
#endif
		return -1;
	}
	return 0;
}

int serialport::sRead(char *bufferstring) {

	int bytesread;

	if (1 == portopen) {
		fcntl(this->fd, F_SETFL, O_NONBLOCK);//don't block the reading from the port
#ifdef DEBUG	
				printf("Read Values From Serial port: ");
#endif
		bytesread = read(this->fd, bufferstring, SERIAL_BUF_LEN);
		if (bytesread < 0) {
#ifdef DEBUG
			printf("ERROR: can't read from serial!\n");
#endif
			return 0;
		} else {
#ifdef DEBUG
			printf("OK: read %d bytes ''\n", bytesread);
#endif
		}
	} else {
#ifdef DEBUG
		printf("\nERROR: Port Not open\n");
#endif
		return -1;
	}
	return bytesread;
}
