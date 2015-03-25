//============================================
// Test van de average klasse
// jdv
//============================================
#include <iostream>
#include <cstdlib>

#include "debug.h"
#include "Positie.h"
#include "Average.h"

int main() {

	std::cout <<"--- Start average test ---" << std::endl;
	int i,j;
	Positie addpos;
	Average rollingavg;
	j=0;
	for(i=0;i<16;i++)
	{
		addpos.setX(j);
		addpos.setY(j);
		addpos.setAngle(j);
		rollingavg.addInputVal(addpos);
		rollingavg.calcAverage();
		std::cout << "---intput nr:" << j << "---" << std::endl;
		addpos.print();
		std::cout << "---average nr:" << j << "---" << std::endl;
		rollingavg.print();
		j++;
	}


	return 0;
}
