/*
* Author: Floris De Smedt - EAVISE/VISICS
*
* main.cpp: The main program code
*/


#include <iostream>
#include "Manager.h"
#include "Point.h"



using namespace std;

int main(){
	Manager M;
	M.AddRobot("R2D2",Point(15,15));
	M.AddRobot("Morpheus",Point(40,28));
	M.AddRobot("Neo",Point(16,74));
	M.AddRobot("Trinity",Point(20,17));
	
	cout << endl << "---------------" << endl;

	M.PrintRobots();
	cout << endl << "---------------" << endl;
	M.DeleteRobot("Neo");

	cout << endl << "---------------" << endl;

	M.Move("R2D2",Point(50,23));

	cout << endl << "---------------" << endl;
	M.PrintRobots();

	cout << endl << "---------------" << endl;
	cout << "Ending the program" <<endl;

return 0;
}

