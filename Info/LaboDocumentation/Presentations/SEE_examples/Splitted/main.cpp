#include <iostream>
#include <cstring>
#include "Robot.h"

using namespace std;

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