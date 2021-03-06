#ifndef HOEK_H_
#define HOEK_H_

//System includes
#include 	<iostream>
#include 	<stdlib.h>		//Use this to process Ctype string atoi()
#include 	<math.h>

#include 	"debug.h"

#define 	PI          3.14159265
#define 	MAXSPEED	100
#define 	MINSPEED	50
#define 	TRESLOW 3

using namespace std;

class Hoek {

private:
    int 	i_Angle;
    char 	c_Direction;
    int 	i_Speed;
    int 	i_Distance;

public:
			~Hoek();
			Hoek();

	int 	getAngle();
	char 	getDirection();
	int 	getSpeed();
	int  	getAfstand();
	void 	setAfstand(int i_Afstand);
	void 	setAngle(int Angle);
	void 	setDirection(char Direction);
	void 	setSpeed(int Speed);
	void 	BepaalHoek(int Xr,int Yr,int Xb,int Yb,int Beta);
    void 	BepaalSnelheid();
    void 	BepaalAfstand(int Xr,int Yr,int Xb,int Yb);
};

#endif
