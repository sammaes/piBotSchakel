/*
* Author: Floris De Smedt - EAVISE/VISICS 
*
* NoConstructor example: when no constructor is defined, the implicit default constructor is used
*/

#include <iostream>
#include <cstring>

using namespace std;

class Robot{
public:
	/*	Robot(string name="robot",int MSpeed=10){
			this->name = name;
			this->MaxSpeed = MSpeed;
		}
	  */  
		string getName(){
			return this->name;
		}

		void DriveAtMax(){
			cout << this->getName() << ":\t"; 
			cout << "Driving at speed " << this->MaxSpeed << endl;
		}
		void setName(string name){
			this->name = name;
		}

		void setMaxSpeed(int speed){
			this->MaxSpeed = speed;
		}
private:
	string name;
	int MaxSpeed;
};

int main(){
Robot R1;
R1.setName("R2D2");
R1.setMaxSpeed(50);

//R1.MaxSpeed = 70; //gets a compilation error. MaxSpeed is private

R1.DriveAtMax();

return 0;
}