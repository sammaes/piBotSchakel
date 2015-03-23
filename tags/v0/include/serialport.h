
#ifndef SERIAL_H_
#define SERIAL_H_

#include <stdio.h>   	/* Standard input/output definitions */
#include <string>  	/* String function definitions */
#include <unistd.h>  	/* UNIX standard function definitions */
#include <fcntl.h>   	/* File control definitions */
#include <errno.h>   	/* Error number definitions */
#include <termios.h> 	/* POSIX terminal control definitions */
#include <sys/types.h>
#include <sys/stat.h>

#define PORT "/dev/ttyUSB0"
//#define PORT "/dev/ttyS1"
#define DATABITS 8
#define STOPBITS 1
#define FLOWCONTROL 0
#define _POSIX_SOURCE 1 /* POSIX compliant source */

#define SERIAL_BUF_LEN 100
#define FALSE 0
#define TRUE 1

#define DEBUG

using namespace std;

class serialport {

private:
    int fd; 
    int portopen; // if 1  port is open if 0 port is closed

public:
    ~serialport();
    serialport();
    serialport(string port);
    void clearBuffer();
    int sWrite(string);
    int sRead(char *);
};

#endif
