/*
* Author: Floris De Smedt - EAVISE/VISICS 
*
* Destructor example
*/


#include <iostream>
#include <cstring>

using namespace std;

class Robot{
public:
		Robot(string name="robot",int MSpeed=10){
			this->name = name;
			this->MaxSpeed = MSpeed;
		}
	    
		string getName(){
			return this->name;
		}

		void DriveAtMax(){
			cout << this->getName() << ":\t"; 
			cout << "Driving at speed " << this->MaxSpeed << endl;
		}
		~Robot(){
			cout << "Deleting the robot " << this->getName() << endl;
		}
private:
	string name;
	int MaxSpeed;
};

int main(){
Robot R1("R2D2",50);
Robot R2("Morpheus",30);
Robot R3;

//R1.MaxSpeed = 70; //gets a compilation error. MaxSpeed is private

R1.DriveAtMax();
R2.DriveAtMax();
R3.DriveAtMax();

return 0;
}