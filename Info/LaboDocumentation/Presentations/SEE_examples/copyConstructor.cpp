/*
* Author: Floris De Smedt - EAVISE/VISICS 
*
* copyConstructor example: use a copy constructor to let the pointer of each object point to the correct variable
*/

#include <iostream>

using namespace std;

class Robot{
public:
	Robot(){
		cout << "Setting variable" << endl;
		this->a = 5;
		b = &a;
	}

/* Copy constructor */
	Robot( const Robot& other ){
		cout << "Copy constructor" << endl;
		this->a = other.a;
		this->b = &(this->a);
	}

/*assignment constructor*/
	Robot& operator=( const Robot& rhs ){
		cout << "Assignment constructor" << endl;
		this->a = rhs.a;
		this->b = &(this->a);
	}
	
	void changeB(int b){
		*(this->b) = b;
	}
	
	void Print(){
		cout << "A is " << a << endl;
	}

	~Robot(){
		cout << "Deleting a Robot" << endl;
	}
private:
	int a;
	int *b;
};


int main(){
	Robot R1;
	Robot R2 = R1;
	Robot R3;
	R3 = R1;

	R2.changeB(15);
	R3.changeB(28);
	R1.Print();

return 0;
}