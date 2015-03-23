/*
* Author: Floris De Smedt - EAVISE/VISICS 
*
* Protected example: demonstration of the protected access specifier
*/

#include <iostream>
#include <cstring>

using namespace std;

class Point{
public:
	void setX(int x){
		this->x = x;
	}
	void setY(int y){
		this->y = y;
	}
	int getX(){
		return this->x;
	}

	int getY(){
		return this->y;
	}
	
private:
	int x;
	int y;
};

class Locatable{
public:
	void PrintLocation(){
		cout << "Location is (" << this->coords.getX() << ", " << this->coords.getY() << ")" << endl; 
	}

	void setCoords(int x, int y){
		this->coords.setX(x);
		this->coords.setY(y);
	}
protected:
	Point Coords2;

private:
	Point coords;
};

class Robot: public Locatable{
public:
	Robot(): driveSpeed(50),name("R2D2"){
		
	}

	string getName(){
		return this->name;
	}

	void PrintLocation(){
		cout << "From Robot class: ";
		Locatable::PrintLocation();
	}

	void PrintRobot(){
		this->PrintLocation();
		cout << "This robot has name " << this->getName() << " and maximum speed " << this->driveSpeed << endl;
	}

	void ChangeCoords(){
		this->Coords2.setX(15);
		this->Coords2.setY(15);
	//	this->coords.setX(15); //coords is private in parent class
	//	this->coords.setY(15); //coords is private in parent class
	
		setCoords(28,15);
	}
private:
	string name;
	int driveSpeed;
};

int main(){
Locatable L1;
L1.setCoords(15,30);
L1.PrintLocation();

cout << "Creating a robot" << endl;

Robot R1;
R1.ChangeCoords();
R1.PrintLocation();
return 0;
}