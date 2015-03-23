#include <iostream>
#include <cstring>

using namespace std;

class Robot{
public:
		Robot(string name="robot",int MSpeed=10); 
		string getName();

		void DriveAtMax();

private:
	string name;
	int MaxSpeed;
};