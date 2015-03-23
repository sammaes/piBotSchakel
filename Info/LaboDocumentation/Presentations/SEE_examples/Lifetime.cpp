/*
* Author: Floris De Smedt - EAVISE/VISICS 
*
* Lifetime example: demonstrating the lifetime of objects (difference dynamic allocation and automatic)
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

/*Dynamic */
Robot *R3 = new Robot("Neo", 150);


R1.DriveAtMax();
R2.DriveAtMax();
R3->DriveAtMax();

delete R3;
cout << "Printed after driving" << endl;

return 0;
}