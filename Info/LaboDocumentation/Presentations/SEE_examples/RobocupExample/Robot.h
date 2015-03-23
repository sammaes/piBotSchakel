/*
* Author: Floris De Smedt - EAVISE/VISICS
*
* Robot.h 
*/

#ifndef H_ROBOT
#define H_ROBOT

#include <iostream>
#include "Point.h"


using namespace std;


class Robot{
	public:
		Robot(string name, Point Location);	
		void DriveTo(Point Destination);
		string getName();
		void PrintRobot();
		void PrintPosition();
		~Robot();
	private:
		string name;
		Point Location;

};
#endif