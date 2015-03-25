
//#include <iostream>
#include "Average.h"

#ifdef DEBUGAVERAGE
		#include <iostream>
#endif // DEBUGAVERAGE


Average::Average()
{
	currentIndex = 0;
}

int Average::getNuberSamp()
{
	return NUMSAMPLES;
}

Positie Average::getAverage()
{
	return average;
}

void Average::calcAverage()
{
	int i;
	Positie sumvals;

	for(i=0;i<NUMSAMPLES;i++)
	{
		sumvals.setX(averagebuffer[i].getX() + sumvals.getX());
		sumvals.setY(averagebuffer[i].getY() + sumvals.getY());
		sumvals.setAngle(averagebuffer[i].getAngle() + sumvals.getAngle());
	}

	sumvals.setX(sumvals.getX()/NUMSAMPLES);
	sumvals.setY(sumvals.getY()/NUMSAMPLES);
	sumvals.setAngle(sumvals.getAngle()/NUMSAMPLES);

	average = sumvals;
}

Positie Average::getCalcAverage()
{
	this->calcAverage();
	return average;
}

Positie Average::getCalcAverage(Positie val)
{
	this->addInputVal(val);
	this->calcAverage();
	return average;
}

void Average::addInputVal(Positie val)
{
	averagebuffer[currentIndex] = val;
	if(currentIndex == NUMSAMPLES){
		currentIndex = 0;
	}else{
		currentIndex++;
	}
}

void Average::print() {
	#ifdef DEBUGAVERAGE
		std::cout << "averagex:" << this->getAverage().getX() << std::endl;
		std::cout << "averagey:" << this->getAverage().getY() << std::endl;
		std::cout << "averagehoek:" << this->getAverage().getAngle()	<< std::endl;
	#endif // DEBUGAVERAGE
}
