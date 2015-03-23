#include <iostream>
#include <cstring>
#include "Robot.h"

using namespace std;

		Robot::Robot(string name,int MSpeed){
			this->name = name;
			this->MaxSpeed = MSpeed;
		}
	    
		string Robot::getName(){
			return this->name;
		}

		void Robot::DriveAtMax(){
			cout << this->getName() << ":\t"; 
			cout << "Driving at speed " << this->MaxSpeed << endl;
		}
