/*
* Author: Floris De Smedt - EAVISE/VISICS 
*
* Overloading example: Multiple functions can have the same name. 
* They can be distinguished by the arguments given
*/

#include <iostream>
#include <cstring>

using namespace std;

void Print(int value){
	cout << value << " from int-Print function" << endl;
}

void Print(string value){
	cout << value << " From string-print function" << endl;
}

int main(){
	int val=15;
	string text= "This is going to be seen on screen";

	Print(val);
	Print(text);


	return 0;
}
