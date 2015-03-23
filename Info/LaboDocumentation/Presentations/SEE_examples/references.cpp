/*
 * Author: Floris De Smedt - EAVISE/VISICS
 *
 * References example: references can be used to circumvent pointers. They can be used just like the original variable 
 * and by using them as an argument with the function, the original variable is modified without passing the whole data-
 * structure through memory
 */
#include <iostream>
#define SIZE 20

using namespace std;

struct Structuur{
	int value[SIZE];
};

void PrintStructuur(Structuur S){
	for(int i=0;i<SIZE;i++){
		cout << '\t' <<  S.value[i] << endl;
	}
}

void AlterStructuur(Structuur S){
	/*
	 * Since the argument is past by value, a local copy is made
	 */
	for(int i=0;i<SIZE;i++){
		S.value[i] += 50;
	}
}

void AlterStructuurRef(Structuur &S){
	/*
	 * Since the argument is past by reference, we are working
	 * in the same data-space as the original variable
	 */
	for(int i=0;i<SIZE;i++){
		S.value[i] += 50;
	}
}

int main(){
	Structuur S;
/* Create content for the structure */
	for(int i=0;i<SIZE;i++){
		S.value[i] = i;
	}

	cout << "Before Altering" << endl;
	PrintStructuur(S);
	cout << "Alter with no reference" << endl;
	AlterStructuur(S);
	PrintStructuur(S);
	cout << "Alter with reference" << endl;
	AlterStructuurRef(S);
	PrintStructuur(S);

return 0;
}
