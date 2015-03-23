/*
* Author: Floris De Smedt - EAVISE/VISICS
*
* Robot.cpp
*/
#include "Point.h"
#include "Robot.h"

using namespace std;


		Robot::Robot(string name, Point Location):Location(Location),name(name){
		}

		void Robot::DriveTo(Point Destination){
			cout << "I, " << this->getName() << ", am now on ";
			Location.Print();
			cout << " and I have to go to "; 
			Destination.Print();
			cout << endl;
			cout << "This means a relative movement of ";
			Point(Destination.getX()-Location.getX(),Destination.getY()-Location.getY()).Print();
			cout << endl;
		}

		string Robot::getName(){
			return this->name;
		}

		void Robot::PrintPosition(){
			this->Location.Print();
		}

		void Robot::PrintRobot(){
			cout << "My name is " << this->getName() << " and I am at location ";
			this->PrintPosition();
			cout << endl;
		}

		Robot::~Robot(){
			cout << "deleting robot " << this->getName() << endl;
		}