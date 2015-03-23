/*
* Author: Floris De Smedt - EAVISE/VISICS
*
* Manager.h
*/

#ifndef H_MANAGER
#define H_MANAGER

#include <iostream>
#include <vector>
#include "Robot.h"
#include "Point.h"

using namespace std;

class Manager{
	public:
		void AddRobot(string name, Point Location);
		void DeleteRobot(string name);
		void PrintRobots();
		void Move(string name, Point P);
		~Manager();
	private:
		vector<Robot*> RBots;
		int FindPosition(string name);

};
#endif