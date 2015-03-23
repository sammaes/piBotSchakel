/*
* Author: Floris De Smedt - EAVISE/VISICS 
*
* Polymorphism example: the type of the object is determined at runtime
*/

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

class Figure{
public:
	virtual string getType() = 0; // makes it impossible to create an object of class Figure
	void setType(string t){
		this->type=t;
	}
protected:
	string type;
};

class Square: public Figure{
public:
	Square(){
		this->setType("Square");
	}
	string getType(){
		return this->type;
	}
private:

};

class Triangle: public Figure{
public:
	Triangle(){
		this->setType("Triagle");
	}
	string getType(){
		return this->type;
	}
private:

};

class Circle: public Figure{
public:
	Circle(){
		this->setType("Circle");
	}
	string getType(){
		return this->type;
	}
private:

};

void ProcessChoice(char c){
Figure *F;
switch(c){
	case 't':
		F = new Triangle;
		cout << "Choice was " << F->getType() << endl;
		break;
	case 'c':
		F = new Circle;
		cout << "Choice was " << F->getType() << endl;
		break;
	case 's':
		F = new Square;
		cout << "Choice was " << F->getType() << endl;
		break;
	default: 
		cout << "No valid choice!" << endl;
}
}


int main(){

//Figure F; //compile error since Figure is pure virtual

cout << "Give your choice: " << endl;
cout << "t: Triagle " << endl;
cout << "c: Circle " << endl;
cout << "s: square " << endl;
char Choice = getchar();
ProcessChoice(Choice);


return 0;
}
